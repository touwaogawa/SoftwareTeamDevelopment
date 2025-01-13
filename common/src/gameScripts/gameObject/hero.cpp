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

Hero::Hero(Player* player, HeroInfo heroInfo, Physics* physics)
    : GameObject()
    , mHeroInfo(heroInfo)
    , mPlayer(player)
{
    HeroBaseStatus heroBaseStatus;
    switch (mHeroInfo.beyType) {
    case BeyType::Shuriken: {
        heroBaseStatus = {
            2.0f,
            3.0f,
            18.0f,
            12.0f,
            0.3f,
            50.0f,
            9.8f
        };
    } break;
    case BeyType::Hexagram: {
        heroBaseStatus = {
            6.0f,
            6.0f,
            3.0f,
            10.0f,
            0.3f,
            50.0f,
            9.8f
        };
    } break;
    case BeyType::Snowflake: {
        heroBaseStatus = {
            6.0f,
            6.0f,
            3.0f,
            10.0f,
            0.3f,
            50.0f,
            9.8f
        };
    } break;
    default:
        std::cout << "BeyType error Hero" << std::endl;
        break;
    }
    mBaseStatus = heroBaseStatus;

    mPlayer->SetHero(this);
    // std::cout << "hero constructor" << std::endl;
    mBaseStatus.gravity
        = 9.8f;

    // RigidBody setting
    RigidBody* rigidBody  = new RigidBody(this, rp3d::BodyType::DYNAMIC, physics);
    rp3d::RigidBody* rprb = rigidBody->GetRp3dRogidBody();
    rprb->enableGravity(false);
    rprb->setMass(mBaseStatus.mass);
    rprb->setAngularLockAxisFactor(rp3d::Vector3(0, 1, 0));

    rp3d::Vector3 position(0.0f, 1.3f, 0.0f);
    rp3d::Quaternion rotation; // 回転なし
    rp3d::Transform offset(position, rotation);

    reactphysics3d::decimal radius = 1.3f; // 半径

    rp3d::CollisionShape* shape = physics->GetPhysicsCommon().createSphereShape(radius);
    rp3d::Collider* collider    = rprb->addCollider(shape, offset);
    collider->getMaterial().setFrictionCoefficient(mBaseStatus.traction);

    AddComponent(rigidBody);
}