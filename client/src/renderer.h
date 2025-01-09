#pragma once
#include "../../utils/src/math.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

class Camera;
class Renderer {
public:
    static bool Init(float window_w, float window_h);
    static void ShutDown();

    static bool Load();   // シーンの最初で呼び出し
    static void UnLoad(); // シーンの終了で呼び出し
    static void Draw();
    static class Texture* GetTexture(const std::string& fileName);
    static class Mesh* GetMesh(const std::string& fileName);
    static void AddMeshRenderer(class MeshRenderer* meshRenderer);
    static void RemoveMeshRenderer(class MeshRenderer* meshRenderer);
    // static void SetViewMatrix(const Matrix4& view) { mView = view; }
    static void AddCamera(const std::string& cameraName, Camera* camera)
    {
        mCameras.emplace(cameraName, camera);
    }
    static void RemoveCamera(const std::string& cameraName)
    {
        mCameras.erase(cameraName);
    }
    static void UseCamera(const std::string& cameraName);

private:
    static SDL_Window* mWindow;
    static SDL_GLContext mContext;

    static float mWindowWidth;
    static float mWindowHeight;

    static class Shader* mMeshShader;
    static class Shader* mDepthShader;
    static class Shader* mShadowMeshShader;

    static std::unordered_map<std::string, class Texture*> mTextures;
    static std::unordered_map<std::string, class Mesh*> mMeshes;
    static std::vector<class MeshRenderer*> mMeshRenderers;

    // カメラ情報
    static std::unordered_map<std::string, Camera*> mCameras;
    static Camera* mCamera;

    static GLuint mDepthMapFBO;
    static GLuint mDepthMap;

    static void Draw3DObjects();
};