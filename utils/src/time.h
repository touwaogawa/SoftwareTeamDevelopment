#pragma once
#include <chrono>

class Time {
public:
    static bool Init(int fps);

    // フレームごとに呼び出されるメソッド
    static void UpdateFrame();

    /// @brief Return time step from previous frame
    /// @return time step (second)
    static float GetTimeStep()
    {
        std::chrono::duration<float> duration = mTime - mLastTime;
        return duration.count();
    }
    static float GetStaticTimeStepSecond()
    {
        return 1.0f / mFps;
    }

private:
    static int mFps;
    static int mFrameTime;
    // static int frameCount;
    static std::chrono::time_point<std::chrono::high_resolution_clock> mTime;
    static std::chrono::time_point<std::chrono::high_resolution_clock> mLastTime;
};