#include "hero.h"
#include "../../component/rigidBody.h"
#include "../../component/transform.h"
#include "../../physics.h"
#include "../../scene.h"
#include "../components/behaviour/heroMove.h"
#include "bey.h"
#include "rider.h"
#include <iostream>
Hero::Hero(HeroInfo heroInfo, Physics* physics)
    : GameObject()
    , mHeroInfo(heroInfo)
{
    // std::cout << "hero constructor" << std::endl;
    mBaseStatus.gravity = 9.8f;

    // RigidBody setting
    RigidBody* rigidBody  = new RigidBody(this, rp3d::BodyType::DYNAMIC, physics);
    rp3d::RigidBody* rprb = rigidBody->GetRp3dRogidBody();
    rprb->enableGravity(false);
    rprb->setMass(2.0f);
    rprb->setAngularLockAxisFactor(rp3d::Vector3(0, 1, 0));

    rp3d::Vector3 position(0.0f, 1.0f, 0.0f);
    rp3d::Quaternion rotation; // 回転なし
    rp3d::Transform offset(position, rotation);

    reactphysics3d::decimal radius = 2.0f; // 半径

    rp3d::CollisionShape* shape = physics->GetPhysicsCommon().createSphereShape(radius);
    rprb->addCollider(shape, offset);
    AddComponent(rigidBody);
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
