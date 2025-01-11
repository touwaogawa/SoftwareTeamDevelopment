#include "main.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, Mix_Chunk*> A::mixs;
int main(int argc, char* argv[])
{
    // SDL初期化
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) != (MIX_INIT_MP3 | MIX_INIT_OGG)) {
        std::cerr << "Mix_Init Error: " << Mix_GetError() << std::endl;
        return false;
    }

    // SDL_mixer初期化
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Mix_OpenAudio Error: " << Mix_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    // 音声ファイルの読み込み
    static Mix_Chunk* sound = Mix_LoadWAV("Tropical_Waves.mp3");
    if (!sound) {
        std::cerr << "Mix_LoadWAV Error: " << Mix_GetError() << std::endl;
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    // 音声の再生
    Mix_PlayChannel(-1, sound, 0);

    // 再生を待つ（3秒間）
    SDL_Delay(30000);

    // リソース解放
    Mix_FreeChunk(sound);
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}
