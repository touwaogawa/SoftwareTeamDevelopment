#pragma once

#include <SDL2/SDL_mixer.h>
#include <string>

class Sound{
public:
    Sound();
    ~Sound();
    
    // BGMをロードして再生
    bool PlayBGM(const std::string& file, int loop = -1);
    // BGMを停止
    void StopBGM();
    // BGMを一時停止
    void PauseBGM();
    // BGMを再開
    void ResumeBGM();

    // SEをロードして再生
    void PlaySE(const std::string& file, int loop = 0);
    // SEを停止
    void StopSE();

    // 音量を設定（0-128）
    void SetBGMVolume(int volume);
    void SetSEVolume(int volume);
private:
};