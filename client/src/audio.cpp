#include "audio.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>

std::unordered_map<std::string, Mix_Music*> Audio::mMix_Musics;
std::unordered_map<std::string, Mix_Chunk*> Audio::mMix_Chunks;

bool Audio::Init()
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG)) {
        std::cerr << "Mix_Init Error: " << Mix_GetError() << std::endl;
        return false;
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        std::cerr << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}
void Audio::PlayMusic(Mix_Music* music)
{
    if (Mix_PlayMusic(music, -1) == -1) {
        printf("Failed to play music: %s\n", Mix_GetError());
    }
}
void Audio::PlayMusic(const std::string& fileName)
{
    PlayMusic(GetMixMusic(fileName));
}
void Audio::FadeInMusic(Mix_Music* music, int fadeTimeMilliSecond)
{
    if (Mix_FadeInMusic(music, -1, fadeTimeMilliSecond) == -1) {
        printf("Failed to FadeIn music: %s\n", Mix_GetError());
    }
}
void Audio::FadeInMusic(const std::string& fileName, int fadeTimeMilliSecond)
{
    FadeInMusic(GetMixMusic(fileName), fadeTimeMilliSecond);
}

void Audio::SetMusicVolume(float degree)
{
    if (degree < 0.0f)
        degree = 0.0f;
    else if (degree > 1.0f)
        degree = 1.0f;

    Mix_VolumeMusic(MIX_MAX_VOLUME * degree);
}

void Audio::PlayChunk(Mix_Chunk* chunk)
{
    if (chunk) {
        Mix_PlayChannel(-1, chunk, 0);

    } else {
        std::cout << "Play chunk error. chunk is nullptr" << std::endl;
    }
}
void Audio::PlayChunk(const std::string& fileName)
{
    PlayChunk(GetMixChunk(fileName));
}

void Audio::SetChunkVolume(float degree)
{
    if (degree < 0.0f)
        degree = 0.0f;
    else if (degree > 1.0f)
        degree = 1.0f;

    Mix_Volume(-1, MIX_MAX_VOLUME * degree);
}

Mix_Music* Audio::GetMixMusic(const std::string& fileName)
{
    Mix_Music* music = nullptr;
    auto iter        = mMix_Musics.find(fileName);
    if (iter != mMix_Musics.end()) {
        music = iter->second;
    } else {
        music = Mix_LoadMUS(fileName.c_str());
        if (music) {
            mMix_Musics.emplace(fileName, music);
        } else {
            Mix_FreeMusic(music);
            music = nullptr;
        }
    }
    return music;
}

Mix_Chunk* Audio::GetMixChunk(const std::string& fileName)
{
    Mix_Chunk* chunk = nullptr;
    auto iter        = mMix_Chunks.find(fileName);
    if (iter != mMix_Chunks.end()) {
        chunk = iter->second;
    } else {
        chunk = Mix_LoadWAV(fileName.c_str());
        if (chunk) {
            mMix_Chunks.emplace(fileName, chunk);
        } else {
            Mix_FreeChunk(chunk);
            chunk = nullptr;
        }
    }
    return chunk;
}

void Audio::Unload()
{
    for (const auto& [key, music] : mMix_Musics) {
        if (music) {
            Mix_FreeMusic(music);
        }
    }
    mMix_Musics.clear();

    for (const auto& [key, chunk] : mMix_Chunks) {
        if (chunk) {
            Mix_FreeChunk(chunk);
        }
    }
    mMix_Chunks.clear();
}

void Audio::ShutDown()
{
    Mix_CloseAudio();
}