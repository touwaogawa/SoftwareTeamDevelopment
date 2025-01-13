#include "player.h"
#include "../components/behaviour/playerMove.h"
#include "hero.h"
#include <iostream>
PlayerInfo::PlayerInfo()
    : id(0)
    , name("player")
{
    heroInfo.riderType = RiderType::BaseHuman;
    heroInfo.beyType   = BeyType::Shuriken;
}
PlayerInfo::PlayerInfo(int p_id, const char p_name[8], RiderType p_riderType, BeyType p_beyType)
    : id(p_id)
{
    strncpy(name, p_name, sizeof(name) - 1); // 安全にコピー
    name[sizeof(name) - 1] = '\0';           // 文字列の終端を保証
    heroInfo.riderType     = p_riderType;
    heroInfo.beyType       = p_beyType;
}
Player::Player(PlayerInfo playerInfo)
    : GameObject()
    , mPlayerInfo(playerInfo)
{
    // std::cout << "player constructor" << std::endl;
}

Player::~Player()
{
}