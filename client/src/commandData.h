#pragma once
#include "math.h"
struct CommandData {
    bool attack1 = false;
    bool attack2 = false;
    bool jump    = false;
    Vector2 moveAxis;
    Vector2 subAxis;
    int frame; // フレーム番号
};

void CommandDataCout(CommandData cd);