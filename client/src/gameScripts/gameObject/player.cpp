#include "player.h"
#include "../components/behaviour/playerMove.h"
#include "hero.h"
#include <iostream>
Player_C::Player_C(PlayerInfo playerInfo, const std::string& tag)
    : Player(playerInfo, tag)
{
}
