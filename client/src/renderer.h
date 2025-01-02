#pragma once
#include "../../utils/src/math.h"
#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

class Renderer {
public:
    static bool Init(float window_w, float window_h);
    static void ShutDown();

    static bool Load();   // シーンの最初で呼び出し
    static void UnLoad(); // シーンの終了で呼び出し
    static void Draw();
    static class Mesh* GetMesh(const std::string& fileName);
    static void AddMeshRenderer(class MeshRenderer* meshRenderer);
    static void RemoveMeshRenderer(class MeshRenderer* meshRenderer);
    static void SetViewMatrix(const Matrix4& view) { mView = view; }

private:
    static SDL_Window* mWindow;
    static SDL_GLContext mContext;

    static float mWindowWidth;
    static float mWindowHeight;

    static class Shader* mMeshShader;
    static std::unordered_map<std::string, class Mesh*> mMeshes;
    static std::vector<class MeshRenderer*> mMeshRenderers;

    static Matrix4 mView;
    static Matrix4 mProjection;
};