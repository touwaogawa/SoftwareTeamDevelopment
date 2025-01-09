#include "renderer.h"
#include "../../common/src/component/transform.h"
#include "../../common/src/gameObject.h"
#include "../../utils/src/math.h"
#include "component/camera.h"
#include "component/meshRenderer.h"
#include "component/sprite.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
#include "vertexArray.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

SDL_Window* Renderer::mWindow       = nullptr;
SDL_GLContext Renderer::mContext    = nullptr;
float Renderer::mWindowWidth        = 0.0f;
float Renderer::mWindowHeight       = 0.0f;
Shader* Renderer::mMeshShader       = nullptr;
Shader* Renderer::mDepthShader      = nullptr;
Shader* Renderer::mShadowMeshShader = nullptr;
Shader* Renderer::mSpriteShader     = nullptr;
std::unordered_map<std::string, class Texture*> Renderer::mTextures;
std::unordered_map<std::string, class Mesh*> Renderer::mMeshes;
std::vector<class MeshRenderer*> Renderer::mMeshRenderers;
std::vector<class Sprite*> Renderer::mSprites;
std::unordered_map<std::string, Camera*> Renderer::mCameras;
Camera* Renderer::mCamera           = nullptr;
GLuint Renderer::mDepthMapFBO       = 0;
GLuint Renderer::mDepthMap          = 0;
VertexArray* Renderer::mSpriteVerts = nullptr;

bool Renderer::Init(float window_w, float window_h)
{
    mWindowWidth  = window_w;
    mWindowHeight = window_h;
    mWindow       = SDL_CreateWindow("OpenGL Cube", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, static_cast<int>(mWindowWidth), static_cast<int>(mWindowHeight), SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!mWindow) {
        std::cout << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_GLContext context = SDL_GL_CreateContext(mWindow);
    if (!context) {
        std::cout << "OpenGL context could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Renderer::ShutDown()
{
    SDL_DestroyWindow(mWindow);
}

bool Renderer::Load()
{
    CreateSpriteVerts();
    mMeshShader = new Shader();
    if (!mMeshShader->Load("shaders/default.vert", "shaders/default.frag")) {
        std::cout << "Failed Shader load" << std::endl;
        return false;
    }
    mDepthShader = new Shader();
    if (!mDepthShader->Load("shaders/createDepth.vert", "shaders/null.frag")) {
        std::cout << "Failed Shader load" << std::endl;
        return false;
    }
    mShadowMeshShader = new Shader();
    if (!mShadowMeshShader->Load("shaders/shadowMesh.vert", "shaders/shadowMesh.frag")) {
        std::cout << "Failed Shader load" << std::endl;
        return false;
    }
    mSpriteShader = new Shader();
    if (!mSpriteShader->Load("shaders/sprite.vert", "shaders/sprite.frag")) {
        std::cout << "Failed Shader load" << std::endl;
        return false;
    }
    mSpriteShader->Use();
    // Set the view-projection matrix
    Matrix4 spriteViewProj = Matrix4::CreateSimpleViewProj(mWindowWidth, mWindowHeight);
    mSpriteShader->SetMatrixUniform("viewProjection", spriteViewProj);

    glGenFramebuffers(1, &mDepthMapFBO);
    glGenTextures(1, &mDepthMap);
    glBindTexture(GL_TEXTURE_2D, mDepthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
        1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glBindFramebuffer(GL_FRAMEBUFFER, mDepthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, mDepthMap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        std::cout << "Depth Framebuffer not complete!" << std::endl;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    return true;
}
void Renderer::UnLoad()
{

    for (auto mesh : mMeshes) {
        delete mesh.second;
    }
    mMeshes.clear();
    delete mMeshShader;

    for (auto texture : mTextures) {
        delete texture.second;
    }
    mTextures.clear();

    for (auto camera : mCameras) {
        delete camera.second;
    }
    mCameras.clear();
}
void Renderer::Draw()
{
    // std::cout << "Draw" << std::endl;
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);

    Draw3DObjects();

    // Sprites
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    mSpriteShader->Use();
    mSpriteVerts->Bind();
    for (auto sprite : mSprites) {
        // std::cout << "Sprite" << std::endl;
        if (sprite->GetVisible()) {
            sprite->Draw(mSpriteShader);
        }
    }

    // 表示
    SDL_GL_SwapWindow(mWindow);
}

Texture* Renderer::GetTexture(const std::string& fileName)
{
    Texture* tex = nullptr;
    auto iter    = mTextures.find(fileName);
    if (iter != mTextures.end()) {
        tex = iter->second;
    } else {
        tex = new Texture();
        if (tex->Load(fileName)) {
            mTextures.emplace(fileName, tex);
        } else {
            delete tex;
            tex = nullptr;
        }
    }
    return tex;
}

Mesh* Renderer::GetMesh(const std::string& fileName)
{

    Mesh* m   = nullptr;
    auto iter = mMeshes.find(fileName);
    if (iter != mMeshes.end()) {
        m = iter->second;
    } else {
        m = new Mesh();
        if (m->LoadObjFile(fileName)) {
            mMeshes.emplace(fileName, m);
        } else {
            delete m;
            m = nullptr;
        }
    }
    return m;
}

void Renderer::AddMeshRenderer(MeshRenderer* meshRenderer)
{
    mMeshRenderers.push_back(meshRenderer);
}
void Renderer::RemoveMeshRenderer(MeshRenderer* meshRenderer)
{
    auto end = std::remove(mMeshRenderers.begin(), mMeshRenderers.end(), meshRenderer);
    mMeshRenderers.erase(end, mMeshRenderers.end());
}
void Renderer::AddSprite(Sprite* sprite)
{
    int myDrawOrder = sprite->GetDrawOrder();
    auto iter       = mSprites.begin();
    for (;
         iter != mSprites.end();
         ++iter) {
        if (myDrawOrder < (*iter)->GetDrawOrder()) {
            break;
        }
    }

    // Inserts element before position of iterator
    mSprites.insert(iter, sprite);
}
void Renderer::RemoveSprite(Sprite* sprite)
{
    std::cout << "Remove Sprite" << std::endl;
    auto end = std::remove(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(end, mSprites.end());
}

void Renderer::UseCamera(const std::string& cameraName)
{
    Camera* camera = mCameras.find(cameraName)->second;
    mCamera        = camera;
}

void Renderer::Draw3DObjects()
{
    // デプス取得----------------------
    mDepthShader->Use();

    Matrix4 lightProjection, lightView;
    Matrix4 lightSpaceMatrix;
    Vector3 lightPos(5.0f, 10.0f, 8.0f);

    // 正射影行列（平行光源用）
    lightProjection = Matrix4::CreateOrtho(30.0f, 30.0f, 1.0f, 30.0f);
    // ビュー行列
    lightView = Matrix4::CreateLookAt(lightPos, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

    lightSpaceMatrix = lightView * lightProjection;

    // シャドウマップをレンダリング
    glViewport(0, 0, 1024, 1024);
    glBindFramebuffer(GL_FRAMEBUFFER, mDepthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);

    // シェーダーに lightSpaceMatrix を渡す
    mDepthShader->Use();
    mDepthShader->SetMatrixUniform("lightSpaceMatrix", lightSpaceMatrix);

    // シーンをレンダリング
    for (MeshRenderer* meshRenderer : mMeshRenderers) {
        meshRenderer->Draw(mDepthShader);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 描画----------------------
    glViewport(0, 0, mWindowWidth, mWindowHeight);
    mShadowMeshShader->Use();

    Vector3 viewPos;
    Matrix4 view;
    Matrix4 projection;
    projection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(40.0f), mWindowWidth, mWindowHeight, 0.1f, 150.0f);
    if (mCamera == nullptr) {
        // std::cout << "mCamera == nullptr" << std::endl;
        viewPos = Vector3(10.0f, 40.0f, -40.0f);
        view    = Matrix4::CreateLookAt(viewPos, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
    } else {
        viewPos = mCamera->GetOwner()->GetTransform()->GetWorldPosition();
        view    = Matrix4::CreateTranslation(viewPos);
        view *= mCamera->GetOwner()->GetTransform()->GetWorldMatrix().GetRotationPart();
    }

    // ライトのプロパティ
    mShadowMeshShader->SetVectorUniform("lightPos", lightPos);
    mShadowMeshShader->SetVectorUniform("viewPos", viewPos);

    // 色の設定
    Vector3 diffuseLightColor(1.0f, 1.0f, 1.0f);
    Vector3 ambientLightColor(0.53f, 0.81f, 0.92f);
    mShadowMeshShader->SetVectorUniform("diffuseLightColor", diffuseLightColor);
    mShadowMeshShader->SetVectorUniform("ambientLightColor", ambientLightColor);

    // アンビエントライトの強度
    float ambientStrength = 0.8f;
    mShadowMeshShader->SetFloatUniform("ambientStrength", ambientStrength);

    // ビュー、プロジェクション
    mShadowMeshShader->SetMatrixUniform("viewProjection", view * projection);
    mShadowMeshShader->SetMatrixUniform("lightSpaceMatrix", lightSpaceMatrix);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mDepthMap);
    mShadowMeshShader->SetIntUniform("shadowMap", 1);

    // 各メッシュ
    for (MeshRenderer* meshRenderer : mMeshRenderers) {
        meshRenderer->Draw(mShadowMeshShader);
    }
}

void Renderer::CreateSpriteVerts()
{
    float vertices[] = {
        // 三角形1
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, // top left
        0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, // bottom right

        // 三角形2
        0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f   // top left
    };
    const void* ptr = static_cast<const void*>(vertices);
    // std::cout << "Create Sprite verts before new" << std::endl;
    mSpriteVerts = new VertexArray(ptr, 6, VertexArray::Layout::PosNormTex);
}