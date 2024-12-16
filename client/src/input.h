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
    static bool ProcessInput();

    // PCキーボード関係(SDL)
    static bool GetKey(SDL_Scancode scancode);
    static bool GetKeyDown(SDL_Scancode scancode);
    static bool GetKeyUp(SDL_Scancode scancode);

    // ゲームパッドとジョイコン共通
    static bool GetButton(std::string buttonName);
    static bool GetButtonDown(std::string buttonName);
    static bool GetButtonUp(std::string buttonName);
    //-1~1の範囲で指定した名前の値が返される。
    static float GetAxis(std::string axisName);

private:
    // ジョイコンはひとつしかつながない前提なのでリストにしない
    //  static joyconlib_t mJoyConLastState;
    static SDL_Event mEvent;
    static const Uint8* mKeyboardState;
    static Uint8 mPrevKeyboardState[SDL_NUM_SCANCODES];
    static joyconlib_t mPrevJoyCon_t;
    static joyconlib_t mJoyCon_t;
    static bool isJoyConConnected;
    static SDL_GameController* mController;
};