#include "time.h"
#include <SDL2/SDL.h>
#include <chrono>
int Time::mFps       = 60;
int Time::mFrameTime = 1000 / 60;
int Time::frameCount = 0;
std::chrono::time_point<std::chrono::high_resolution_clock> mTime;
std::chrono::time_point<std::chrono::high_resolution_clock> mLastTime;
Time::Time()
{
}

bool Time::Init(int fps)
{
    Time::mFrameTime = 1000 / Time::mFps;
    Time::mLastTime  = std::chrono::high_resolution_clock::now();
    return true;
}

void Time::UpdateFrame()
{
    // 経過時間を計測
    mTime              = std::chrono::high_resolution_clock::now();
    auto frameDuration = std::chrono::duration_cast<std::chrono::milliseconds>(mTime - mLastTime).count();

    // 次のフレームまでの待機時間を計算
    int delayTime = mFrameTime - frameDuration;

    // 次のフレームまで待機（遅延を入れる）
    if (delayTime > 0) {
        SDL_Delay(delayTime); // 指定時間だけ待機
    }

    mLastTime = mTime; // 現在の時間を次のフレームの基準に
}

auto Time::GetTime()
{
    return mTime;
}