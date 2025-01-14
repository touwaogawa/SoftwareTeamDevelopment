#include "hero.h"
#include "../components/behaviour/heroMove.h"
#include "bey.h"
#include "rider.h"
#include <iostream>
Hero_S::Hero_S(Scene* scene, Transform* parent, Vector3 initialPos, HeroInfo heroInfo)
    : Hero(scene, parent, initialPos, heroInfo, new HeroMove_S(this))
{
    mRider = new Rider_S(scene, mTransform, heroInfo.riderType);
    mBey   = new Bey_S(scene, mTransform, heroInfo.beyType);
    std::cout << "hero_s constructer" << std::endl;
}
