#pragma once
#include "../../utils/src/math.h"
#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

class Renderer {
public:
    Renderer();
    ~Renderer();
    static bool Init(float window_w, float window_h);
    static void ShutDown();

    bool Load();
    void Draw();
    class Mesh* GetMesh(const std::string& fileName);
    void AddMeshRenderer(class MeshRenderer* meshRenderer);
    void RemoveMeshRenderer(class MeshRenderer* meshRenderer);
    void SetViewMatrix(const Matrix4& view) { mView = view; }

private:
    static SDL_Window* mWindow;
    static SDL_GLContext mContext;

    static float mWindowWidth;
    static float mWindowHeight;

    // シェーダ
    class Shader* mMeshShader;

    // メッシュ
    std::unordered_map<std::string, class Mesh*> mMeshes;

    // メッシュレンダラー
    std::vector<class MeshRenderer*> mMeshRenderers;

    Matrix4 mView;
    Matrix4 mProjection;
};