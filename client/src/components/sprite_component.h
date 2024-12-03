#pragma once

#include "component.h"
#include <SDL2/SDL.h>

class SpriteComponent : public Component {
public:
    void CopyTexture();

private:
    SDL_Texture* mTexture;
    SDL_Rect src;
    SDL_Rect dst;
};