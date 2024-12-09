#pragma once
#include "render_manager.h"
#include "scenes/scene.h"
#include "scenes/test_scene.h"
#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

class Game {
public:
    typedef enum {
        TITLE,
        HOME,
        BATTLE,
        RESULT,
        TEST,
        SCENE_MAX
    } Scenes;

    Game();

    bool Initialize();
    void RunLoop();
    void Shutdown();

    void LoadScene(Scene* scene);
    void UnLoadScene();
    Scene* GetScene() const;
    void ChangeScene(const std::string& sceneName); // シーンを切り替える

private:
    bool mIsRunning;

    // シーン
    Scene* mCurrentScene; // 現在のシーン
    TestScene mTestScene; // 開発用

    RenderManager mRenderManager;

    int mLastTime;    // フレームが始まった時間
    int mCurrentTime; // 色々処理が終わった時間

    void ProcessInput();
    void Update();
    void RenderScene();
};
