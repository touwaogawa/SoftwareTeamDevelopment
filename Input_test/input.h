#pragma once

#include <SDL2/SDL.h>
#include <string>
// #include <joyconlib>

class Input {
public:
    Input();

    // 接続に成功したら trueを返す
    static bool ConnectController();

    // メンバにキーの状態を更新, 毎フレーム呼ばれる
    static void ProcessInput();

    // PCキーボード関係(SDL)
    static bool GetKey(SDL_KeyCode keyCode);
    static bool GetKeyDown(SDL_KeyCode keyCode);
    static bool GetKeyUp(SDL_KeyCode keyCode);

    // ゲームパッドとジョイコン共通
    static bool GetJoyConButton(std::string buttonName);
    static bool GetJoyConButtonDown(std::string buttonName);
    static bool GetJoyConButtonUp(std::string buttonName);
    //-1~1の範囲で指定した名前の値が返される。
    static float GetAxis(std::string axisName);

private:
    // ジョイコンはひとつしかつながない前提なのでリストにしない
    //  static joyconlib_t mJoyConLastState;
};