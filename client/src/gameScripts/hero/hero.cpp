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
    float traction,
    float mass)
    : GameObject(scene, parent, new HeroMove(this))
    , mBey(new Bey(mScene, mTransform))
    , mRider(new Rider(mScene, mTransform))
    , mWalkAcceleration(walkAcceleration)
    , mMaxWalkSpeed(maxWalkSpeed)
    , mInitialDushSpeed(initialDushSpeed)
    , mDushAcceleration(dushAcceleration)
    , mMaxRunSpeed(maxRunSpeed)
    , mTraction(traction)
    , mMass(mass)
    , currentStatus(HeroStatus::Idle)
    , currentMoveAxis(0.0f, 0.0f)
    , currentSpeed(0.0f)
{
}

Hero::~Hero()
{
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
