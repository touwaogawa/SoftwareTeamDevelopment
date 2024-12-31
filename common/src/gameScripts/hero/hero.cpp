#include "hero.h"
#include "../../component.h"
#include "../../components/transform.h"
#include "bey.h"
#include "heroMove.h"
#include "rider.h"

Hero::Hero(Scene* scene, Transform* parent, HeroBaseStatus heroBaseStatus)
    : GameObject(scene, parent, new HeroMove(this))
    , mBey(new Bey(mScene, mTransform, BeyType::Shuriken))
    , mRider(new Rider(mScene, mTransform, RiderType::BaseHuman))
    , mBaseStatus(heroBaseStatus)
{
}

Hero::~Hero()
{
}

float Hero::GetWalkAcceleration() const
{
    return mBaseStatus.walkAcceleration;
}
float Hero::GetMaxWalkSpeed() const
{
    return mBaseStatus.maxWalkSpeed;
}
float Hero::GetInitialDushSpeed() const
{
    return mBaseStatus.initialDushSpeed;
}
float Hero::GetDushAcceleration() const
{
    return mBaseStatus.dushAcceleration;
}
float Hero::GetMaxRunSpeed() const
{
    return mBaseStatus.maxRunSpeed;
}
float Hero::GetTraction() const
{
    return mBaseStatus.traction;
}

Bey* Hero::GetBey() const
{
    return mBey;
}
Rider* Hero::GetRider() const
{
    return mRider;
}