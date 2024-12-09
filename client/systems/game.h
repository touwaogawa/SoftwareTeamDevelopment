#pragma once
#include "render_pipeline.h"
#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

class Game {
public:
    Game();

    bool Initialize();
    bool Load();
    void RunLoop();
    void Shutdown();

private:
    bool mIsRunning;
};
