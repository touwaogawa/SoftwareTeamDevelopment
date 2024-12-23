#include "hero.h"
#include "../../component.h"
#include "../../components/transform.h"
#include "bey.h"
#include "heroMove.h"
#include "rider.h"

Hero::Hero(Scene* scene, Transform* parent,
    float walkAcceleration,
    float maxWalkSpeed,
    float initialDushSpeed,
    float dushAcceleration,
    float maxRunSpeed,
    float traction)
    : GameObject(scene, parent, new HeroMove(this))
    , mBey(new Bey(mScene, mTransform))
    , mRider(new Rider(mScene, mTransform))
    , mWalkAcceleration(walkAcceleration)
    , mMaxWalkSpeed(maxWalkSpeed)
    , mInitialDushSpeed(initialDushSpeed)
    , mDushAcceleration(dushAcceleration)
    , mMaxRunSpeed(maxRunSpeed)
    , mTraction(traction)
    , mHeroStatus(HeroStatus::Idle)
{
}

Hero::~Hero()
{
}

HeroStatus Hero::GetStatus() const
{
    return mHeroStatus;
}

float Hero::GetWalkAcceleration() const
{
    return mWalkAcceleration;
}
float Hero::GetMaxWalkSpeed() const
{
    return mMaxWalkSpeed;
}
float Hero::GetInitialDushSpeed() const
{
    return mInitialDushSpeed;
}
float Hero::GetDushAcceleration() const
{
    return mDushAcceleration;
}
float Hero::GetMaxRunSpeed() const
{
    return mMaxRunSpeed;
}
float Hero::GetTraction() const
{
    return mTraction;
}