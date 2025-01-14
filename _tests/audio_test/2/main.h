#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <unordered_map>

class A {
public:
    static std::unordered_map<std::string, Mix_Chunk*> mixs;

private:
};