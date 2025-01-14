#include "hero.h"
#include "../../component/rigidBody.h"
#include "../../component/transform.h"
#include "../../physics.h"
#include "../../scene.h"
#include "../components/behaviour/heroMove.h"
#include "bey.h"
#include "player.h"
#include "rider.h"
#include <iostream>

Hero::Hero(Player* player, HeroInfo heroInfo, Physics* physics, const std::string& tag)
    : GameObject("Hero", tag)
    , mHeroInfo(heroInfo)
    , mPlayer(player)
    , mActionFrame(0)
    , mStopFrame(0)
    , mDownFrame(0)
{
    // std::cout << "hero constructor" << std::endl;

    mPlayer->SetHero(this);

    HeroBaseStatus heroBaseStatus;
    switch (mHeroInfo.beyType) {
    case BeyType::Shuriken: {
        heroBaseStatus.WalkSpeed         = 4.0f;
        heroBaseStatus.initialDushSpeed  = 3.0f;
        heroBaseStatus.dushAcceleration  = 1.5f;
        heroBaseStatus.maxDushSpeed      = 9.5f;
        heroBaseStatus.traction          = 0.93f;
        heroBaseStatus.mass              = 50.0f;
        heroBaseStatus.bigJumpVelocity   = 12.0f;
        heroBaseStatus.smallJumpVelocity = 8.0f;
        heroBaseStatus.airMoveSpeed      = 2.0f;
        heroBaseStatus.attackSpeed       = 23.0f;
    } break;
    case BeyType::Hexagram: {
        heroBaseStatus.WalkSpeed         = 3.0f;
        heroBaseStatus.initialDushSpeed  = 3.0f;
        heroBaseStatus.dushAcceleration  = 1.5f;
        heroBaseStatus.maxDushSpeed      = 7.5f;
        heroBaseStatus.traction          = 0.9f;
        heroBaseStatus.mass              = 50.0f;
        heroBaseStatus.bigJumpVelocity   = 12.0f;
        heroBaseStatus.smallJumpVelocity = 8.0f;
        heroBaseStatus.airMoveSpeed      = 1.0f;
        heroBaseStatus.attackSpeed       = 23.0f;
    } break;
    case BeyType::Snowflake: {
        heroBaseStatus.WalkSpeed         = 3.0f;
        heroBaseStatus.initialDushSpeed  = 3.0f;
        heroBaseStatus.dushAcceleration  = 1.5f;
        heroBaseStatus.maxDushSpeed      = 7.5f;
        heroBaseStatus.traction          = 0.9f;
        heroBaseStatus.mass              = 50.0f;
        heroBaseStatus.bigJumpVelocity   = 4.0f;
        heroBaseStatus.smallJumpVelocity = 2.0f;
        heroBaseStatus.airMoveSpeed      = 1.0f;
        heroBaseStatus.attackSpeed       = 23.0f;
    } break;
    default:
        std::cout << "BeyType error Hero" << std::endl;
        break;
    }
    mBaseStatus = heroBaseStatus;

    // RigidBody setting
    RigidBody* rigidBody  = new RigidBody(this, rp3d::BodyType::DYNAMIC, physics);
    rp3d::RigidBody* rprb = rigidBody->GetRp3dRogidBody();
    // rprb->enableGravity(true);
    rprb->setMass(mBaseStatus.mass);
    rprb->setAngularLockAxisFactor(rp3d::Vector3(0, 1, 0));

    rp3d::Vector3 position(0.0, 1.3, 0.0);
    rp3d::Quaternion rotation(rp3d::Quaternion::identity()); // 回転なし
    rp3d::Transform offset(position, rotation);

    reactphysics3d::decimal radius = 1.3f; // 半径

    rp3d::CollisionShape* shape = physics->GetPhysicsCommon().createSphereShape(radius);
    rp3d::Collider* collider    = rprb->addCollider(shape, offset);
    collider->getMaterial().setFrictionCoefficient(mBaseStatus.traction);
    collider->getMaterial().setBounciness(0.3f);

    AddComponent(rigidBody);
}