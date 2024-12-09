#include "input.h"
#include <joyconlib.h>
#include <string>

// ジョイコンの状態を保持する変数
joyconlib_t Input::mJoyCon_t;
joyconlib_t Input::mPrevJoyCon_t = {0};
SDL_Event Input::mEvent;

// 初期化
bool Input::Init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    joycon_err err = joycon_open(&mJoyCon_t, JOYCON_R);
    if (JOYCON_ERR_NONE != err) {
        printf("joycon open failed: %d\n", err);
        return false;
    }

    return true;
}

// 終了
void Input::ShutDown() {
    joycon_close(&mJoyCon_t);
    SDL_Quit();
}

// 接続に成功したら trueを返す
bool Input::ConnectController() {
    if(joycon_open(&mJoyCon_t, JOYCON_R) == JOYCON_ERR_NONE){
        //ジョイコンの状態を取得
        joycon_get_state(&mJoyCon_t);

        // 前回の状態を更新
        mPrevJoyCon_t = mJoyCon_t;
        return true;
    }else {
        return false;
    }
}

// メンバにキーの状態を更新, 毎フレーム呼ばれる
void Input::ProcessInput() {
    SDL_PollEvent(&mEvent);

    // 前回の状態を更新
    mPrevJoyCon_t = mJoyCon_t;
    //ジョイコンの状態を取得
    joycon_get_state(&mJoyCon_t);

}

// PCキーボード関係(SDL)
bool Input::GetKey(SDL_Keycode keyCode) {
    return mEvent.key.keysym.sym == keyCode;
    
}

bool Input::GetKeyDown(SDL_Keycode keyCode) {
     // 実装例: キーが押された瞬間を検出するロジックを追加
    return false;
}

bool Input::GetKeyUp(SDL_Keycode keyCode) {
     // 実装例: キーが離された瞬間を検出するロジックを追加
    return false;
}

// ゲームパッドとジョイコン共通
bool Input::GetButton(std::string buttonName) {
    if (buttonName == "A") return mJoyCon_t.button.btn.A;
    if (buttonName == "B") return mJoyCon_t.button.btn.B;
    if (buttonName == "X") return mJoyCon_t.button.btn.X;
    if (buttonName == "Y") return mJoyCon_t.button.btn.Y;
    return false;
}

bool Input::GetButtonDown(std::string buttonName) {
    if (buttonName == "A") return mJoyCon_t.button.btn.A && !mPrevJoyCon_t.button.btn.A;
    if (buttonName == "B") return mJoyCon_t.button.btn.B && !mPrevJoyCon_t.button.btn.B;
    if (buttonName == "X") return mJoyCon_t.button.btn.X && !mPrevJoyCon_t.button.btn.X;
    if (buttonName == "Y") return mJoyCon_t.button.btn.Y && !mPrevJoyCon_t.button.btn.Y;
    return false;
}

bool Input::GetButtonUp(std::string buttonName) {
    if (buttonName == "A") return !mJoyCon_t.button.btn.A && mPrevJoyCon_t.button.btn.A;
    if (buttonName == "B") return !mJoyCon_t.button.btn.B && mPrevJoyCon_t.button.btn.B;
    if (buttonName == "X") return !mJoyCon_t.button.btn.X && mPrevJoyCon_t.button.btn.X;
    if (buttonName == "Y") return !mJoyCon_t.button.btn.Y && mPrevJoyCon_t.button.btn.Y;
    return false;
}
