#pragma once
#include "../../utils/src/math.h"
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

class CameraComponent;
class LightComponent;
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
    static void AddEffectRenderer(class MeshRenderer* meshRenderer);
    static void RemoveEffectRenderer(class MeshRenderer* meshRenderer);

    static void AddSpriteRenderer(class SpriteRenderer* spriteRenderer);
    static void RemoveSpriteRenderer(class SpriteRenderer* spriteRenderer);
    static void AddBillbourdRenderer(class SpriteRenderer* spriteRenderer);
    static void RemoveBillbourdRenderer(class SpriteRenderer* spriteRenderer);

    static void SetCameraComponent(CameraComponent* cameraComponent) { mCameraComponent = cameraComponent; }
    static CameraComponent* GetCameraComponent() { return mCameraComponent; }

    static void SetLightComponent(LightComponent* lightComponent) { mLightComponent = lightComponent; }
    static LightComponent* GetLightComponent() { return mLightComponent; }

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
    static class Shader* mEffectShader;
    static class Shader* mBillbourdShader;

    static std::unordered_map<std::string, class Texture*> mTextures;
    static std::unordered_map<std::string, class Mesh*> mMeshes;

    static std::vector<class MeshRenderer*> mMeshRenderers;
    static std::vector<class MeshRenderer*> mEffectRenderers;
    static std::vector<class SpriteRenderer*> mSpriteRenderers;
    static std::vector<class SpriteRenderer*> mBillbourdRenderers;

    // カメラ情報
    static CameraComponent* mCameraComponent;
    static LightComponent* mLightComponent;

    // 描画基本情報
    static Vector3 mViewPos;    // カメラの位置
    static Matrix4 mView;       // カメラのビュー
    static Matrix4 mProjection; // カメラのプロジェクション

    static Vector3 mLightPos;        // ライトの位置
    static Matrix4 mLightView;       // ライトのビュー
    static Matrix4 mLightProjection; // ライトのプロジェクション
    static Vector3 mLightColor;      // ライトの色

    static float mAmbientLightStrength;
    static Vector3 mAmbientLightColor;

    static GLuint mDepthMapFBO;
    static GLuint mDepthMap;

    // スプライト
    static VertexArray* mSpriteVerts;

    static void Draw3DObjects();
    static void DrawEffects();
    static void DrawBillbourds();
    static void DrawSprites();
    static void CreateSpriteVerts();
};