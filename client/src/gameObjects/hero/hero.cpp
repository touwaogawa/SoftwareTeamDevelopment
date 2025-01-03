#include "hero.h"
#include "bey.h"
#include "heroMove.h"
#include "rider.h"

Hero_C::Hero_C(Scene* scene, Transform* parent, Vector3 initialPos, HeroInfo heroInfo)
    : Hero(scene, parent, initialPos,
          heroInfo,
          new HeroMove_C(this))
{
    mRider = new Rider_C(scene, mTransform, heroInfo.riderType);
    mBey   = new Bey_C(scene, mTransform, heroInfo.beyType);
}
