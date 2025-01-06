#include "hero.h"
#include "../../component/collider.h"
#include "../../component/rigidBody.h"
#include "../../component/transform.h"
#include "../../physics.h"
#include "../../scene.h"
#include "../components/behaviour/heroMove.h"
#include "bey.h"
#include "rider.h"
#include <iostream>
Hero::Hero(Scene* scene, Transform* parent, Vector3 initialPos, HeroInfo heroInfo, HeroMove* heroMove)
    : GameObject(scene, parent, heroMove)
    , mHeroInfo(heroInfo)
{
    std::cout << "hero constructer" << std::endl;
    mBaseStatus.gravity = 9.8f;
    mTransform->SetWorldPosition(initialPos);
    // RigidBody setting
    RigidBody* rigidBody = new RigidBody(this, rp3d::BodyType::DYNAMIC, mScene->GetPhysics());
    rigidBody->mRigidBody->enableGravity(false);
    rigidBody->mRigidBody->setMass(2.0f);
    rigidBody->mRigidBody->setAngularLockAxisFactor(rp3d::Vector3(0, 1, 0));
    AddComponent(rigidBody);

    // Collider setting
    rp3d::Vector3 position(0.0f, 1.0f, 0.0f);
    rp3d::Quaternion rotation; // 回転なし
    rp3d::Transform transform(position, rotation);

    Collider* collider = new Collider(this,
        mScene->GetPhysics()->GetPhysicsWorld(),
        Physics::mPhysicsCommon.createSphereShape(1.0),
        rigidBody->mRigidBody,
        transform);
    AddComponent(collider);
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
