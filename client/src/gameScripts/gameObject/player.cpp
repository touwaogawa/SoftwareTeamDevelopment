#include "player.h"
#include "../components/behaviour/playerMove.h"
#include "hero.h"
#include <iostream>
Player_C::Player_C(Scene* scene, PlayerInfo playerInfo, const int* currentSceneFrame)
    : Player(scene, playerInfo, currentSceneFrame,
          new PlayerMove_C(this))
{
    mHero = new Hero_C(scene, mTransform, GetInitialHeroPos(playerInfo.id), playerInfo.heroInfo);
}
