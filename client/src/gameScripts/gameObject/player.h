#pragma once
#include "../../../../common/src/gameScripts/gameObject/player.h"
#include <string>

class Player_C : public Player {
public:
    Player_C(PlayerInfo playerInfo, const std::string& tag);
    ~Player_C() override = default;

private:
};