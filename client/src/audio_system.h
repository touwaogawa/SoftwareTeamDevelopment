#pragma once

// #include <stdio.h>
#include <SDL2/SDL_mixer.h>
#include <string>

namespace Audio{
    class BGM{
    public:
        BGM();
        ~BGM();
        
        // BGMをロードして再生
        bool PlayBGM(const std::string& file, int loop = -1);
        // BGMを停止
        void StopBGM();
        // BGMを一時停止
        void PauseBGM();
        // BGMを再開
        void ResumeBGM();

       

        // 音量を設定（0-128）
        void SetBGMVolume(int volume);
        
    private:
        
    };
    class SE{
    public:
        SE();
        ~SE();
         // SEをロードして再生
        void PlaySE(const std::string& file, int loop = 0);
        // SEを停止
        void StopSE();
        void SetSEVolume(int volume);
    private:
    }
}

