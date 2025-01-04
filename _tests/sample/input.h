#pragma once
#include < SDL2 / SDL.h>

class Input {
public:
    static bool GetKeyDown(SDL_Keycode keycode)
    {
        return true;
    }
    static bool GetKeyUp(SDL_Keycode keycode)
    {
        return false;
    }
};