#include "renderer.h"
#include "components/meshRenderer.h"
#include "mesh.h"
#include "shader.h"
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
//
#include <glm/gtc/type_ptr.hpp>

SDL_Window* Renderer::mWindow    = nullptr;
SDL_GLContext Renderer::mContext = nullptr;
float Renderer::mWindowWidth     = 0.0f;
float Renderer::mWindowHeight    = 0.0f;

Renderer::Renderer()
{
    mMeshShader = new Shader();
}

Renderer::~Renderer()
{

    delete mMeshShader;
}
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
    mView       = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitZ, Vector3::UnitY);
    mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f), mWindowWidth, mWindowHeight, 10.0f, 10000.0f);
    if (!mMeshShader->Load("shaders/vertex_shader.glsl", "shaders/fragment_shader.glsl")) {
        std::cout << "Failed Mesh Shader load" << std::endl;
        return false;
    }
    return true;
}
void Renderer::Draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    mMeshShader->Use();
    glm::mat4 identity = glm::mat4(1.0f);
    glm::vec3 view_pos = glm::vec3(0.0f, -1.5f, -70.0f);

    glm::mat4 view = glm::translate(identity, view_pos);
    view *= glm::rotate(identity, glm::radians(48.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    // view                 = glm::rotate(view, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 projection = glm::perspective(glm::radians(40.0f), mWindowWidth / mWindowHeight, 0.1f, 150.0f);

    // ライトのプロパティ
    glUniform3f(glGetUniformLocation(mMeshShader->GetProgram(), "lightPos"), 1.2f, 4.0f, 2.0f);
    // glUniform3f(glGetUniformLocation(mMeshShader->GetProgram(), "viewPos"), mView.mat[3][0], mView.mat[3][1], mView.mat[3][2]);
    glUniform3f(glGetUniformLocation(mMeshShader->GetProgram(), "viewPos"), 0.0f, 0.0f, -10.0f);

    // 色の設定
    glUniform3f(glGetUniformLocation(mMeshShader->GetProgram(), "lightColor"), 1.0f, 1.0f, 1.0f);
    glUniform3f(glGetUniformLocation(mMeshShader->GetProgram(), "objectColor"), 0.4f, 0.5f, 0.31f);

    // アンビエントライトの強度
    glUniform1f(glGetUniformLocation(mMeshShader->GetProgram(), "ambientStrength"), 0.6f);

    GLint viewLoc = glGetUniformLocation(mMeshShader->GetProgram(), "view");
    GLint projLoc = glGetUniformLocation(mMeshShader->GetProgram(), "projection");

    // glUniformMatrix4fv(viewLoc, 1, GL_FALSE, mView.GetAsFloatPtr());
    // glUniformMatrix4fv(projLoc, 1, GL_FALSE, mProjection.GetAsFloatPtr());
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    // 各メッシュ
    for (MeshRenderer* meshRenderer : mMeshRenderers) {
        meshRenderer->Draw(mMeshShader);
    }

    // 表示
    SDL_GL_SwapWindow(mWindow);
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