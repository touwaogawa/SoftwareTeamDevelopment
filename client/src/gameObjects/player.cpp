#include "player.h"
#include "hero/hero.h"
#include "playerMove.h"
#include <iostream>
Player_C::Player_C(Scene* scene, PlayerInfo playerInfo, const int* currentSceneFrame)
    : Player(scene, playerInfo, currentSceneFrame,
          new PlayerMove_C(this))
{
    mHero = new Hero_C(scene, mTransform, GetInitialHeroPos(playerInfo.id), playerInfo.heroInfo);
}
