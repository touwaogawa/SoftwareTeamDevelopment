#include "player.h"
#include "../../../utils/src/math.h"
#include "hero/hero.h"
#include "playerMove.h"
#include <iostream>
Player_S::Player_S(Scene* scene, PlayerInfo playerInfo, const int* currentSceneFrame)
    : Player(scene, playerInfo, currentSceneFrame, new PlayerMove_S(this))

{
    mHero = new Hero_S(scene, mTransform, GetInitialHeroPos(playerInfo.id), playerInfo.heroInfo);
    std::cout << "player_s gen" << std::endl;
}