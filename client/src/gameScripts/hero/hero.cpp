#include "hero.h"
#include "../../component.h"
#include "../../components/transform.h"
#include "bey.h"
#include "heroMove.h"
#include "rider.h"

Helo::Helo(Scene* scene, Transform* parent)
    : GameObject(scene, parent, new HeroMove(this))
    , mBey(new Bey(mScene, mTransform))
    , mRider(new Rider(mScene, mTransform))
{
}

Helo::~Helo()
{
}