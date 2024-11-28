#pragma once
#include "client_renderer.h"     //
#include "scenes/client_scene.h" // シーン基底クラスをインクルード
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
    void ProcessInput();
    void UpdateGame();
    void RenderScene();

    bool mIsRunning;
    std::unordered_map<std::string, Scene*> mScenes; // シーンのコレクション
    Scene* mCurrentScene;                            // 現在のシーン
};
