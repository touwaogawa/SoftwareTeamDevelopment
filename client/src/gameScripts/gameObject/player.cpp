#include "player.h"
#include "../../../../common/src/component/transform.h"
#include "../components/behaviour/playerMove.h"
#include "hero.h"
#include <iostream>

Player::Player(PlayerInfo playerInfo, const std::string& tag)
    : GameObject("Player", tag)
    , mPlayerInfo(playerInfo)
    , mPlayrState(PlayerState::Battle)
    , mHero(new Hero(this, playerInfo.heroInfo, tag))
{
    // std::cout << "player constructor" << std::endl;
    SetBehaviour(new PlayerMove(this, mHero));
    mHero->GetTransform()->SetParent(GetTransform());
}