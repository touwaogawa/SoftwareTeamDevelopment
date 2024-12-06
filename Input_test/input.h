#pragma once

#include <SDL2/SDL.h>

enum class KeyCode {
    SPACE,
    ESCAPE
};

enum class JoyConButtonCode {
    A,
    B,
    X,
    y
};

enum class GamePadButtonCode {
    A,
    B,
    X,
    y
};

struct JoyStickState {
    float x;
    float y;
};

// シングルトンパターンクラス
class Input {
public:
    static Input& GetInstance()
    {
        static Input instance; // ローカル静的変数でインスタンスを保持
        return instance;
    }

    // 接続に成功したら trueを返す(joyconよりゲームパッドが優先される)
    bool ConnectController();

    // メンバにキーの状態を保存
    void ProcessInput();

    // PCキーボード関係(SDL)
    bool GetKey(KeyCode keycode);
    bool GetKeyDown(KeyCode keycode);
    bool GetKeyUp(KeyCode keycode);

    // ジョイコン関係
    bool GetJoyConButton(JoyConButtonCode jcbc);
    bool GetJoyConButtonDown(JoyConButtonCode jcbc);
    bool GetJoyConButtonUp(JoyConButtonCode jcbc);
    JoyStickState GetJoyConStickState();
    JoyStickState GetJoyConStickState(JoyStickState& joystickstate);
    JoyStickState GetJoyConStickState(float& JoyStickState_x, float& JoyStickState_y);

    // ゲームパッド関係
    // bool GetGamePadButton(GamePadButtonCode jcbc);
    // bool GetGamePadButtonDown(GamePadButtonCode jcbc);
    // bool GetGamePadButtonUp(GamePadButtonCode jcbc);
    // JoyStickState GetGamePadStickState();
    // JoyStickState GetGamePadStickState(JoyStickState& joystickstate);
    // JoyStickState GetGamePadStickState(float& JoyStickState_x, float& JoyStickState_y);

private:
    // コンストラクタをプライベートにすることで外部でインスタンス化できないように
    Input()
    {
    }

    // コピーコンストラクタと代入演算子を削除して、インスタンスの複製を防ぐ
    Input(const Input&)            = delete;
    Input& operator=(const Input&) = delete;

    // ここに状態を格納するメンバを書く
    // SDL(KeyUpやdownをサポートしてるので多分必要ない)
    // JoyCon joyconlib_t のprevのみ必要かな多分
    // GamePad 何が必要か分からん
};