#include "renderer.h"
#include "../../common/src/component/transform.h"
#include "../../common/src/gameObject.h"
#include "../../utils/src/math.h"
#include "component/billbourdRenderer.h"
#include "component/cameraComponent.h"
#include "component/lightComponent.h"
#include "component/meshRenderer.h"
#include "component/spriteRenderer.h"
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
Shader* Renderer::mEffectShader     = nullptr;
Shader* Renderer::mBillbourdShader  = nullptr;
std::unordered_map<std::string, Texture*> Renderer::mTextures;
std::unordered_map<std::string, Mesh*> Renderer::mMeshes;
std::vector<MeshRenderer*> Renderer::mMeshRenderers;
std::vector<MeshRenderer*> Renderer::mEffectRenderers;
std::vector<SpriteRenderer*> Renderer::mSpriteRenderers;
std::vector<BillbourdRenderer*> Renderer::mBillbourdRenderers;
CameraComponent* Renderer::mCameraComponent = nullptr;
LightComponent* Renderer::mLightComponent   = nullptr;
GLuint Renderer::mDepthMapFBO               = 0;
GLuint Renderer::mDepthMap                  = 0;
VertexArray* Renderer::mSpriteVerts         = nullptr;
Vector3 Renderer::mViewPos;
Matrix4 Renderer::mView;
Matrix4 Renderer::mProjection;
Vector3 Renderer::mLightPos;
Matrix4 Renderer::mLightView;
Matrix4 Renderer::mLightProjection;
Vector3 Renderer::mLightColor         = Vector3(1.0f, 1.0f, 1.0f);
float Renderer::mAmbientLightStrength = 0.8f;
Vector3 Renderer::mAmbientLightColor  = Vector3(0.53f, 0.81f, 0.92f);

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
    mEffectShader = new Shader();
    if (!mEffectShader->Load("shaders/default.vert", "shaders/basic.frag")) {
        std::cout << "Failed Shader load" << std::endl;
        return false;
    }
    mBillbourdShader = new Shader();
    if (!mBillbourdShader->Load("shaders/billbourd.vert", "shaders/sprite.frag")) {
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
        2048, 2048, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
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
    delete mMeshShader;
    delete mDepthShader;
    delete mShadowMeshShader;
    delete mSpriteShader;
    delete mEffectShader;
    delete mBillbourdShader;

    for (auto mesh : mMeshes) {
        delete mesh.second;
    }
    mMeshes.clear();

    for (auto texture : mTextures) {
        delete texture.second;
    }
    mTextures.clear();

    mCameraComponent = nullptr;
}
void Renderer::Draw()
{
    if (mCameraComponent == nullptr) {
        // std::cout << "mCameraComponent == nullptr" << std::endl;
        mViewPos    = Vector3(0.0f, 40.0f, -40.0f);
        mView       = Matrix4::CreateLookAt(mViewPos, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
        mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(40.0f), mWindowWidth, mWindowHeight, 0.1f, 150.0f);
    } else {
        mViewPos    = mCameraComponent->GetOwner()->GetTransform()->GetWorldPosition();
        mView       = mCameraComponent->GetOwner()->GetTransform()->GetWorldMatrix();
        mProjection = mCameraComponent->GetProjection();
    }

    if (mLightComponent == nullptr) {
        // std::cout << "mLightComponent == nullptr" << std::endl;
        mLightPos        = Vector3(5.0f, 30.0f, 8.0f);
        mLightView       = Matrix4::CreateLookAt(mLightPos, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
        mLightProjection = Matrix4::CreateOrtho(40.0f, 40.0f, 1.0f, 100.0f);
        mLightColor      = Vector3(1.0f, 1.0f, 1.0f);
    } else {
        mLightPos        = mLightComponent->GetOwner()->GetTransform()->GetWorldPosition();
        mLightView       = mLightComponent->GetOwner()->GetTransform()->GetWorldMatrix();
        mLightProjection = mLightComponent->GetProjection();
        mLightColor      = mLightComponent->GetColor();
    }

    // std::cout << "Draw" << std::endl;
    glClearColor(0.53f, 0.81f, 0.92f, 1.0f);
    // glClearColor(0.2f, 0.3f, 0.4f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // std::cout << "draw 1" << std::endl;
    Draw3DObjects();
    // std::cout << "draw 2" << std::endl;
    // エフェクト
    DrawEffects();
    // billboard
    DrawBillbourds();
    // Sprites
    DrawSprites();
    // std::cout << "draw 3" << std::endl;
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

void Renderer::AddEffectRenderer(MeshRenderer* meshRenderer)
{
    mEffectRenderers.push_back(meshRenderer);
}
void Renderer::RemoveEffectRenderer(MeshRenderer* meshRenderer)
{
    auto end = std::remove(mEffectRenderers.begin(), mEffectRenderers.end(), meshRenderer);
    mEffectRenderers.erase(end, mEffectRenderers.end());
}

void Renderer::AddSpriteRenderer(SpriteRenderer* spriteRenderer)
{
    int myDrawOrder = spriteRenderer->GetDrawOrder();
    auto iter       = mSpriteRenderers.begin();
    for (;
         iter != mSpriteRenderers.end();
         ++iter) {
        if (myDrawOrder < (*iter)->GetDrawOrder()) {
            break;
        }
    }

    // Inserts element before position of iterator
    mSpriteRenderers.insert(iter, spriteRenderer);
}
void Renderer::RemoveSpriteRenderer(SpriteRenderer* spriteRenderer)
{
    // std::cout << "Remove Sprite" << std::endl;
    auto end = std::remove(mSpriteRenderers.begin(), mSpriteRenderers.end(), spriteRenderer);
    mSpriteRenderers.erase(end, mSpriteRenderers.end());
}

void Renderer::AddBillbourdRenderer(BillbourdRenderer* billbourdRenderer)
{
    int myDrawOrder = billbourdRenderer->GetDrawOrder();
    auto iter       = mBillbourdRenderers.begin();
    for (;
         iter != mBillbourdRenderers.end();
         ++iter) {
        if (myDrawOrder < (*iter)->GetDrawOrder()) {
            break;
        }
    }

    // Inserts element before position of iterator
    mBillbourdRenderers.insert(iter, billbourdRenderer);
}
void Renderer::RemoveBillbourdRenderer(BillbourdRenderer* billbourdRenderer)
{
    // std::cout << "Remove Billbourd" << std::endl;
    auto end = std::remove(mBillbourdRenderers.begin(), mBillbourdRenderers.end(), billbourdRenderer);
    mBillbourdRenderers.erase(end, mBillbourdRenderers.end());
}

void Renderer::Draw3DObjects()
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
    // glBlendFunc(GL_ONE, GL_ZERO);

    // デプス取得----------------------
    mDepthShader->Use();

    // シャドウマップをレンダリング
    glViewport(0, 0, 2048, 2048);
    glBindFramebuffer(GL_FRAMEBUFFER, mDepthMapFBO);
    glClear(GL_DEPTH_BUFFER_BIT);

    // シェーダーに lightSpaceMatrix を渡す
    mDepthShader->SetMatrixUniform("lightSpaceMatrix", mLightView * mLightProjection);

    // シーンをレンダリング
    // std::cout << "meshnum : " << mMeshRenderers.size() << std::endl;
    for (MeshRenderer* meshRenderer : mMeshRenderers) {
        // std::cout << "meshren " << std::endl;
        meshRenderer->Draw(mDepthShader);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 描画----------------------
    glViewport(0, 0, mWindowWidth, mWindowHeight);
    mShadowMeshShader->Use();

    // ライトのプロパティ
    mShadowMeshShader->SetVector3Uniform("lightPos", mLightPos);
    mShadowMeshShader->SetVector3Uniform("viewPos", mViewPos);

    // 色の設定
    mShadowMeshShader->SetVector3Uniform("diffuseLightColor", mLightColor);
    mShadowMeshShader->SetVector3Uniform("ambientLightColor", mAmbientLightColor);

    // アンビエントライトの強度
    mShadowMeshShader->SetFloatUniform("ambientStrength", mAmbientLightStrength);

    // ビュー、プロジェクション
    mShadowMeshShader->SetMatrixUniform("viewProjection", mView * mProjection);
    mShadowMeshShader->SetMatrixUniform("lightSpaceMatrix", mLightView * mLightProjection);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mDepthMap);
    mShadowMeshShader->SetIntUniform("shadowMap", 1);

    // 各メッシュ
    for (MeshRenderer* meshRenderer : mMeshRenderers) {
        meshRenderer->Draw(mShadowMeshShader);
    }
}
void Renderer::DrawEffects()
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);

    glViewport(0, 0, mWindowWidth, mWindowHeight);
    mEffectShader->Use();

    // ビュー、プロジェクション
    mEffectShader->SetMatrixUniform("viewProjection", mView * mProjection);

    // 各メッシュ
    for (MeshRenderer* meshRenderer : mEffectRenderers) {
        // std::cout << "effect ren " << std::endl;
        meshRenderer->Draw(mEffectShader);
    }
}
void Renderer::DrawBillbourds()
{
    glEnable(GL_DEPTH_TEST);
    // glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    glViewport(0, 0, mWindowWidth, mWindowHeight);

    mBillbourdShader->Use();
    // ビュー、プロジェクション
    mBillbourdShader->SetMatrixUniform("projection", mProjection);
    mBillbourdShader->SetMatrixUniform("view", mView);
    // mBillbourdShader->SetVector3Uniform("viewPos", mViewPos);

    // 各メッシュ
    mSpriteVerts->Bind();
    for (auto billBourd : mBillbourdRenderers) {
        // std::cout << "billBourd Ren" << std::endl;
        if (billBourd->GetVisible()) {
            billBourd->Draw(mBillbourdShader);
        }
    }
}
void Renderer::DrawSprites()
{
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glDepthMask(GL_TRUE);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

    glViewport(0, 0, mWindowWidth, mWindowHeight);

    Shader* shader = mSpriteShader;
    shader->Use();
    mSpriteVerts->Bind();
    for (auto sprite : mSpriteRenderers) {
        // std::cout << "Sprite Ren" << std::endl;
        if (sprite->GetVisible()) {
            sprite->Draw(shader);
        }
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