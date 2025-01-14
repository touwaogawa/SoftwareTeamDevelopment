#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <unordered_map>

class Audio {
public:
    static bool Init();

    static void PlayMusic(Mix_Music* music);
    static void PlayMusic(const std::string& fileName);
    static void FadeInMusic(Mix_Music* music, int fadeTimeMilliSecond);
    static void FadeInMusic(const std::string& fileName, int fadeTimeMilliSecond);

    static void StopMusic() { Mix_HaltMusic(); }
    static void FadeOutMusic(int fadeTimeMilliSecond) { Mix_FadeOutMusic(fadeTimeMilliSecond); }

    static void SetMusicVolume(float degree);

    static void PlayChunk(Mix_Chunk* chunk);
    static void PlayChunk(const std::string& fileName);

    static void SetChunkVolume(float degree);

    static Mix_Music* GetMixMusic(const std::string& fileName);
    static Mix_Chunk* GetMixChunk(const std::string& fileName);
    static void Unload();
    static void ShutDown();

private:
    static std::unordered_map<std::string, Mix_Music*> mMix_Musics;
    static std::unordered_map<std::string, Mix_Chunk*> mMix_Chunks;
};