#include "renderer.h"
#include "component/meshRenderer.h"
#include "mesh.h"
#include "shader.h"
#include "texture.h"
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
std::unordered_map<std::string, class Texture*> Renderer::mTextures;
std::unordered_map<std::string, class Mesh*> Renderer::mMeshes;
std::vector<class MeshRenderer*> Renderer::mMeshRenderers;
Matrix4 Renderer::mView       = {};
Matrix4 Renderer::mProjection = {};
GLuint Renderer::mDepthMapFBO = 0;
GLuint Renderer::mDepthMap    = 0;

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
    mMeshShader = new Shader();
    mView       = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitZ, Vector3::UnitY);
    mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f), mWindowWidth, mWindowHeight, 10.0f, 10000.0f);
    if (!mMeshShader->Load("shaders/default.vert", "shaders/default.frag")) {
        std::cout << "Failed Mesh Shader load" << std::endl;
        return false;
    }
    mDepthShader = new Shader();
    if (!mDepthShader->Load("shaders/createDepth.vert", "shaders/null.frag")) {
        std::cout << "Failed Mesh Shader load" << std::endl;
        return false;
    }
    mShadowMeshShader = new Shader();
    if (!mShadowMeshShader->Load("shaders/shadowMesh.vert", "shaders/shadowMesh.frag")) {
        std::cout << "Failed Mesh Shader load" << std::endl;
        return false;
    }

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
}
void Renderer::Draw()
{
    // std::cout << "Draw" << std::endl;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // glm::mat4 lightProjection, lightView;
    // glm::mat4 lightSpaceMatrix;
    glm::vec3 lightPos(0.0f, 8.0f, 5.0f);

    // // 正射影行列（平行光源用）
    // lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 7.5f);
    // // ビュー行列
    // lightView        = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
    // lightSpaceMatrix = lightProjection * lightView;

    // // シャドウマップをレンダリング
    // glViewport(0, 0, 1024, 1024);
    // glBindFramebuffer(GL_FRAMEBUFFER, mDepthMapFBO);
    // glClear(GL_DEPTH_BUFFER_BIT);

    // // シェーダーに lightSpaceMatrix を渡す
    // mDepthShader->Use();
    // mDepthShader->setMat4("lightSpaceMatrix", lightSpaceMatrix);

    // // シーンをレンダリング
    // RenderScene(mDepthShader);

    // glBindFramebuffer(GL_FRAMEBUFFER, 0);

    Shader* shader = mMeshShader;
    shader->Use();
    glm::mat4 identity = glm::mat4(1.0f);
    // glm::vec3 view_pos = glm::vec3(0.0f, -1.5f, -70.0f);

    Vector3 viewpos(10.0f, 40.0f, -40.0f);
    // Vector3 viewpos(0.0f, 0.0f, 0.0f);
    Matrix4 view = Matrix4::CreateLookAt(viewpos, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
    // Matrix4 view   = Matrix4::CreateTranslation(viewpos);
    static float r = 0.0f;
    // view *= Matrix4::CreateRotationX(Math::ToRadians(r));
    // view *= Matrix4::CreateRotationY(Math::ToRadians(r));
    // view *= Matrix4::CreateRotationX(Math::ToRadians(r));
    r += 0.5f;
    // view *= Matrix4::CreateRotationX(Math::ToRadians(-48.0f));

    // glm::mat4 view = glm::translate(identity, view_pos);
    // view *= glm::rotate(identity, glm::radians(48.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // view                 = glm::rotate(view, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    Matrix4 projection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(40.0f), mWindowWidth, mWindowHeight, 0.1f, 1500.0f);
    // glm::mat4 projection = glm::perspective(glm::radians(40.0f), mWindowWidth / mWindowHeight, 0.1f, 1500.0f);

    // ライトのプロパティ
    glUniform3f(glGetUniformLocation(shader->GetProgram(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);
    // glUniform3f(glGetUniformLocation(shader->GetProgram(), "viewPos"), mView.mat[3][0], mView.mat[3][1], mView.mat[3][2]);
    glUniform3f(glGetUniformLocation(shader->GetProgram(), "viewPos"), 0.0f, 0.0f, -10.0f);

    // 色の設定
    Vector3 diffuseLightColor(1.0f, 1.0f, 1.0f);
    Vector3 ambientLightColor(0.7f, 0.9f, 0.9f);
    shader->SetVectorUniform("diffuseLightColor", diffuseLightColor);
    shader->SetVectorUniform("ambientLightColor", ambientLightColor);

    // アンビエントライトの強度
    float ambientStrength = 0.6f;
    shader->SetFloatUniform("ambientStrength", ambientStrength);

    GLint viewLoc = glGetUniformLocation(shader->GetProgram(), "view");
    GLint projLoc = glGetUniformLocation(shader->GetProgram(), "projection");

    // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, mView.GetAsFloatPtr());
    // glUniformMatrix4fv(projLoc, 1, GL_FALSE, mProjection.GetAsFloatPtr());
    shader->SetMatrixUniform("view", view);
    // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    shader->SetMatrixUniform("projection", projection);
    // glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // 各メッシュ
    for (MeshRenderer* meshRenderer : mMeshRenderers) {
        meshRenderer->Draw(shader);
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
