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
    static void UpdateInputStatus();

    // PCキーボード関係(SDL)
    static bool GetKey(SDL_Scancode scancode);
    static bool GetKeyDown(SDL_Scancode scancode);
    static bool GetKeyUp(SDL_Scancode scancode);

    // ganepad用
    static bool GetButton(int buttonName);
    static bool GetButtonDown(int buttonName);
    static bool GetButtonUp(int buttonName);
    //-1~1の範囲で指定した名前の値が返される。
    static float GetAxis(int axisName);
    static float GetAxisRel(int axisName);

    // joycon用
    static bool GetJCButton(std::string buttonName);
    static bool GetJCButtonDown(std::string buttonName);
    static bool GetJCButtonUp(std::string buttonName);
    //-1~1の範囲で指定した名前の値が返される。
    static float GetJCAxis(std::string axisName);

private:
    static SDL_Event mEvent;
    static const Uint8* mKeyboardState;
    static Uint8 mPrevKeyboardState[SDL_NUM_SCANCODES];
    static joyconlib_t mPrevJoyCon_t;
    static joyconlib_t mJoyCon_t;
    static bool isJoyConConnected;
    static SDL_GameController* mController;
    static SDL_Joystick* mJoystick;
    static bool mJoystickButtonState[10];
    static bool mPrevJoystickButtonState[10];
    static float mJoystickAxisState[4];
    static float mPrevJoystickAxisState[4];
};