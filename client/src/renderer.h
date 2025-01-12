#pragma once
#include "../../utils/src/math.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

class Camera;
class VertexArray;

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

    static void AddSpriteRenderer(class SpriteRenderer* Sprite);
    static void RemoveSpriteRenderer(class SpriteRenderer* Sprite);

    static void SetCamera(Camera* camera) { mCamera = camera; }
    static Camera* GetCamera() { return mCamera; }

    static float GetWindowWidth() { return mWindowWidth; }
    static float GetWindowHeight() { return mWindowHeight; }

private:
    static SDL_Window* mWindow;
    static SDL_GLContext mContext;

    static float mWindowWidth;
    static float mWindowHeight;

    static class Shader* mMeshShader;
    static class Shader* mDepthShader;
    static class Shader* mShadowMeshShader;
    static class Shader* mSpriteShader;

    static std::unordered_map<std::string, class Texture*> mTextures;
    static std::unordered_map<std::string, class Mesh*> mMeshes;
    static std::vector<class MeshRenderer*> mMeshRenderers;
    static std::vector<class SpriteRenderer*> mSprites;

    // カメラ情報
    static Camera* mCamera;

    static GLuint mDepthMapFBO;
    static GLuint mDepthMap;

    // スプライト
    static VertexArray* mSpriteVerts;

    static void Draw3DObjects();
    static void CreateSpriteVerts();
};