#pragma once
#include "renderer.h"
#include "scenes/scene.h"
#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

class Game {
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();

    void ChangeScene(const std::string& sceneName); // シーンを切り替える

private:
    bool mIsRunning;

    std::unordered_map<std::string, Scene*> mScenes; // シーンのコレクション
    Scene* mCurrentScene;                            // 現在のシーン

    Renderer mRenderer;

    int mLastTime;    // フレームが始まった時間
    int mCurrentTime; // 色々処理が終わった時間

    void ProcessInput();
    void UpdateGame();
    void RenderScene();
};
