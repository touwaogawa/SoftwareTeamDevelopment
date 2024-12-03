// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "../../common/src/common_math.h"
#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

class Renderer {
public:
    Renderer(class Game* game, int virtual_screen_w, int virtual_screen_h);
    ~Renderer();

    bool Initialize();
    void Shutdown();
    void Draw();

    void AddSprite();
    bool CreateTextureFromPath(const char* filePath);

private:
    bool InitWindowSize(int* window_w, int* window_h);
    void UpdateScreenSize();

    // Game
    class Game* mGame;

    // ゲーム画面テクスチャをレンダラーに貼るときのサイズ
    SDL_Rect mScreenSize;

    // ゲーム画面テクスチャを作る時点でのサイズ
    int mVirtualScreenWidth;
    int mVirtualScreenHeight;

    // Window
    SDL_Window* mWindow;
    // opengl context
    SDL_GLContext mContext;
};