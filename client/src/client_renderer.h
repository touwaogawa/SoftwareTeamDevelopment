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
    Renderer(class Game* game);
    ~Renderer();

    bool Initialize();
    void Shutdown();

    void Draw();
    void CreateTextureFromPath(const char* filePath);

private:
    bool InitWindowSize();
    void UpdateScreenSize(int window_w, int window_h);

    // Game
    class Game* mGame;

    // 実際のウィンドウサイズ
    int mWindowWidth;
    int mWindowHeight;

    // ゲーム画面テクスチャをレンダラーに貼るときのサイズ
    SDL_Rect mScreenSize;

    // ゲーム画面テクスチャを作る時点でのサイズ
    int mVirtualScreenWidth;
    int mVirtualScreenHeight;

    // Window
    SDL_Window* mWindow;
    // Renderer
    SDL_Renderer* mRenderer;

    //
    SDL_Texture* m2dTexture;
    SDL_Texture* m3dTexture;
};