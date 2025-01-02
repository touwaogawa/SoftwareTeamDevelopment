#include "hero.h"
#include "../../component.h"
#include "../../components/transform.h"
#include "bey.h"
#include "heroMove.h"
#include "rider.h"

Hero::Hero(Scene* scene, Transform* parent, HeroInfo heroInfo)
    : GameObject(scene, parent, new HeroMove(this))
    , mHeroInfo(heroInfo)
    , mRider(new Rider(mScene, mTransform, mHeroInfo.riderType))
    , mBey(new Bey(mScene, mTransform, mHeroInfo.beyType))
{
    // 足した答え
    mBaseStatus.gravity = 9.8f;
    // , mBaseStatus(heroBaseStatus)
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
float Hero::GetMass() const
{
    return mBaseStatus.mass;
}
float Hero::GetGravity() const
{
    return mBaseStatus.gravity;
}

Bey* Hero::GetBey() const
{
    return mBey;
}
Rider* Hero::GetRider() const
{
    return mRider;
}