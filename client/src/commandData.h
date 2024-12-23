#pragma once
#include "math.h"
#include <deque>
enum class CommandType {
    Walk,
    Dash,
    Attack,
    Jump,
    Charge,
    CommandTypeNum, // コマンドの数
    CommandEnpty
};
struct CommandData {
    CommandType commandType = CommandType::CommandEnpty; // 無効なコマンド
    Vector2 vector          = {};                        // ベクトルの初期化
    float axis              = 0.0f;                      // 軸の初期化
    int inputFrame          = -1;                        // 無効なフレーム番号
};
