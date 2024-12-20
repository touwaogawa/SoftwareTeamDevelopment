#include "commandData.h"
#include "input.h"
#include <SDL2/SDL.h>
#include <cstring>
#include <iostream>
#include <joyconlib.h>
#include <string>

// ジョイコンの状態を保持する変数
joyconlib_t Input::mJoyCon_t                       = {};
joyconlib_t Input::mPrevJoyCon_t                   = {};
SDL_Event Input::mEvent                            = {};
const Uint8* Input::mKeyboardState                 = nullptr;
Uint8 Input::mPrevKeyboardState[SDL_NUM_SCANCODES] = { 0 };
bool Input::isJoyConConnected                      = false;
SDL_GameController* Input::mController             = nullptr;
SDL_Joystick* Input::mJoystick                     = nullptr;
// 初期化
bool Input::Init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    for (int i = 0; i < SDL_NumJoysticks(); ++i) {
        printf("Joystick %d: %s\n", i, SDL_JoystickNameForIndex(i));
        mJoystick = SDL_JoystickOpen(i); // i はジョイスティックのインデックス
        if (mJoystick == NULL) {
            std::cout << "Failed to open joystick " << i << ": " << SDL_GetError() << std::endl;
            return -1;
        }
    }

    mKeyboardState = SDL_GetKeyboardState(NULL);
    memcpy(mPrevKeyboardState, mKeyboardState, SDL_NUM_SCANCODES);

    return true;
}

// 終了
void Input::ShutDown()
{
    SDL_JoystickClose(mJoystick);
    if (isJoyConConnected)
        joycon_close(&mJoyCon_t);
    SDL_GameControllerClose(mController);
}

// 接続に成功したら trueを返す
bool Input::ConnectController()
{
    if (joycon_open(&mJoyCon_t, JOYCON_R) == JOYCON_ERR_NONE) {
        // ジョイコンの状態を取得
        joycon_get_state(&mJoyCon_t);

        // 前回の状態を更新
        mPrevJoyCon_t = mJoyCon_t;
        return true;
    } else {
        std::cout << "Failed joycon connect" << std::endl;
        return false;
    }
}

// メンバにキーの状態を更新, 毎フレーム呼ばれる
void Input::UpdateInputStatus()
{
    memcpy(mPrevKeyboardState, mKeyboardState, SDL_NUM_SCANCODES); // 前回の状態を更新
    SDL_PollEvent(&mEvent);                                        // キーボードの状態を取得
    if (isJoyConConnected) {
        mPrevJoyCon_t = mJoyCon_t;    // 前回の状態を更新
        joycon_get_state(&mJoyCon_t); // ジョイコンの状態を取得
    }

    // ボタンの入力をチェック
    for (int i = 0; i < SDL_JoystickNumButtons(mJoystick); ++i) {
        if (SDL_JoystickGetButton(mJoystick, i)) {
            std::cout << "Button " << i << " pressed!" << std::endl;
        }
    }
    for (int i = 0; i < SDL_JoystickNumAxes(mJoystick); ++i) {
        Sint16 axis_value = SDL_JoystickGetAxis(mJoystick, i);
        std::cout << "Axis " << i << " value: " << axis_value << std::endl;
    }
}

// PCキーボード関係(SDL)
bool Input::GetKey(SDL_Scancode scancode)
{
    return mKeyboardState[scancode];
}

bool Input::GetKeyDown(SDL_Scancode scancode)
{
    return mKeyboardState[scancode] && !mPrevKeyboardState[scancode];
}

bool Input::GetKeyUp(SDL_Scancode scancode)
{
    return !mKeyboardState[scancode] && mPrevKeyboardState[scancode];
}

// ゲームパッドとジョイコン共通
bool Input::GetButton(std::string buttonName)
{
    if (buttonName == "A")
        return mJoyCon_t.button.btn.A;
    if (buttonName == "B")
        return mJoyCon_t.button.btn.B;
    if (buttonName == "X")
        return mJoyCon_t.button.btn.X;
    if (buttonName == "Y")
        return mJoyCon_t.button.btn.Y;
    if (buttonName == "SL")
        return mJoyCon_t.button.btn.SL_r;
    if (buttonName == "SR")
        return mJoyCon_t.button.btn.SR_r;
    if (buttonName == "Home")
        return mJoyCon_t.button.btn.Home;
    if (buttonName == "Plus")
        return mJoyCon_t.button.btn.Plus;
    return false;
}

bool Input::GetButtonDown(std::string buttonName)
{
    if (buttonName == "A")
        return mJoyCon_t.button.btn.A && !mPrevJoyCon_t.button.btn.A;
    if (buttonName == "B")
        return mJoyCon_t.button.btn.B && !mPrevJoyCon_t.button.btn.B;
    if (buttonName == "X")
        return mJoyCon_t.button.btn.X && !mPrevJoyCon_t.button.btn.X;
    if (buttonName == "Y")
        return mJoyCon_t.button.btn.Y && !mPrevJoyCon_t.button.btn.Y;
    if (buttonName == "SL")
        return mJoyCon_t.button.btn.SL_r && !mPrevJoyCon_t.button.btn.SL_r;
    if (buttonName == "SR")
        return mJoyCon_t.button.btn.SR_r && !mPrevJoyCon_t.button.btn.SR_r;
    if (buttonName == "Home")
        return mJoyCon_t.button.btn.Home && !mPrevJoyCon_t.button.btn.Home;
    if (buttonName == "Plus")
        return mJoyCon_t.button.btn.Plus && !mPrevJoyCon_t.button.btn.Plus;
    return false;
}

bool Input::GetButtonUp(std::string buttonName)
{
    if (buttonName == "A")
        return !mJoyCon_t.button.btn.A && mPrevJoyCon_t.button.btn.A;
    if (buttonName == "B")
        return !mJoyCon_t.button.btn.B && mPrevJoyCon_t.button.btn.B;
    if (buttonName == "X")
        return !mJoyCon_t.button.btn.X && mPrevJoyCon_t.button.btn.X;
    if (buttonName == "Y")
        return !mJoyCon_t.button.btn.Y && mPrevJoyCon_t.button.btn.Y;
    if (buttonName == "SL")
        return mJoyCon_t.button.btn.SL_r && mPrevJoyCon_t.button.btn.SL_r;
    if (buttonName == "SR")
        return mJoyCon_t.button.btn.SR_r && mPrevJoyCon_t.button.btn.SR_r;
    if (buttonName == "Home")
        return mJoyCon_t.button.btn.Home && mPrevJoyCon_t.button.btn.Home;
    if (buttonName == "Plus")
        return mJoyCon_t.button.btn.Plus && mPrevJoyCon_t.button.btn.Plus;
    return false;
}

float Input::GetAxis(std::string axisName)
{
    if (axisName == "JcRStickX")
        return mJoyCon_t.stick.x;
    if (axisName == "JcRStickY")
        return mJoyCon_t.stick.y;
    return false;
}
