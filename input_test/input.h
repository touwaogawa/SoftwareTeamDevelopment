#pragma once

#include <SDL2/SDL.h>
#include <joyconlib.h>
#include <string>

class Input {
public:
    // 初期化
    static bool Init();
    // 終了
    static void ShutDown();

    // 接続に成功したら trueを返す
    static bool ConnectController();

    // メンバにキーの状態を更新, 毎フレーム呼ばれる
    static void ProcessInput();

    // PCキーボード関係(SDL)
    static bool GetKey(SDL_Keycode keyCode);
    static bool GetKeyDown(SDL_Keycode keyCode);
    static bool GetKeyUp(SDL_Keycode keyCode);

    // ゲームパッドとジョイコン共通
    static bool GetButton(std::string buttonName);
    static bool GetButtonDown(std::string buttonName);
    static bool GetButtonUp(std::string buttonName);
    //-1~1の範囲で指定した名前の値が返される。
    static float GetAxis(std::string axisName);

private:
    // ジョイコンはひとつしかつながない前提なのでリストにしない
    //  static joyconlib_t mJoyConLastState;
    static joyconlib_t mJoyCon_t;
    static joyconlib_t mPrevJoyCon_t;
    static SDL_Event mEvent;
};