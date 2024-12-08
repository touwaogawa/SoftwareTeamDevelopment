#pragma once
#include "render_pipeline.h"
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
        SCENE_MAX
    } Scenes;

    Game();

    bool Initialize();
    void RunLoop();
    void Shutdown();

    void LoadScene(Scenes scene);
    void UnLoadScene();
    void ChangeScene(const std::string& sceneName); // シーンを切り替える

private:
    bool mIsRunning;

    int mLastTime;    // フレームが始まった時間
    int mCurrentTime; // 色々処理が終わった時間

    void ProcessInput();
    void UpdateGame();
    void RenderScene();
};
