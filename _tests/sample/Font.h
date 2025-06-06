// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Math.h"
#include <SDL2/SDL_ttf.h>
#include <string>
#include <unordered_map>

class Font {
public:
    Font(class Game* game);
    ~Font();

    // Load/unload from a file
    bool Load(const std::string& fileName);
    void Unload();

    // Given string and this font, draw to a texture
    class Texture* RenderText(const std::string& textKey,
        const Vector3& color = Color::White,
        int pointSize        = 30);

private:
    // Map of point sizes to font data
    std::unordered_map<int, TTF_Font*> mFontData;
    class Game* mGame;
};
