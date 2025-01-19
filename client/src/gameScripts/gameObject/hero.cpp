#include "hero.h"
#include "../../../../common/src/component/rigidBody.h"
#include "../../../../common/src/component/transform.h"
#include "../../../../common/src/physics.h"
#include "../../../../common/src/scene.h"
#include "../../../../common/src/sceneManager.h"
#include "../components/behaviour/heroMove.h"
#include "bey.h"
#include "heroBody.h"
#include "player.h"
#include "rider.h"
#include <iostream>

Hero::Hero(Player* player, HeroInfo heroInfo, const std::string& tag)
    : GameObject("Hero", tag)
    , mHeroInfo(heroInfo)
    , mPlayer(player)
    , mRider(new Rider(this, heroInfo.riderType, tag, mPlayer->GetID()))
    , mBey(new Bey(this, heroInfo.beyType, tag))
    , mHeroBody(new HeroBody(this, tag))
{
    // std::cout << "hero constructor" << std::endl;

    HeroBaseStatus heroBaseStatus;
    switch (mHeroInfo.beyType) {
    case BeyType::Shuriken: {
        heroBaseStatus.mass               = 50.0f; // 質量
        heroBaseStatus.walkAcceleration   = 4.0f;  // 歩行加速
        heroBaseStatus.maxWalkSpeed       = 4.0f;  // 最大歩行スピード
        heroBaseStatus.initialDushSpeed   = 3.0f;  // ダッシュ初速度
        heroBaseStatus.dushAcceleration   = 1.5f;  // ダッシュ加速量
        heroBaseStatus.maxDushSpeed       = 10.5f; // 最大ダッシュ速度
        heroBaseStatus.traction           = 0.9f;  // 地上抵抗
        heroBaseStatus.airAcceleration    = 15.0f; // 空中加速
        heroBaseStatus.maxAirSpeed        = 9.0f;  // 空中最大速度
        heroBaseStatus.airFriction        = 4.0f;  // 空中抵抗
        heroBaseStatus.maxFallSpeed       = 3.0f;  // 最大落下速度
        heroBaseStatus.fastFallSpeed      = 5.0f;  // 急降下速度
        heroBaseStatus.fullJumpVelocity   = 17.0f; // 大ジャンプ初速度
        heroBaseStatus.shortJumpVelocity  = 6.0f;  // 小ジャンプ初速度
        heroBaseStatus.doubleJumpVelocity = 17.0f; // 2段ジャンプ初速
    } break;
    case BeyType::Hexagram: {
        heroBaseStatus.mass               = 50.0f; // 質量
        heroBaseStatus.walkAcceleration   = 4.0f;  // 歩行加速
        heroBaseStatus.maxWalkSpeed       = 4.0f;  // 最大歩行スピード
        heroBaseStatus.initialDushSpeed   = 3.0f;  // ダッシュ初速度
        heroBaseStatus.dushAcceleration   = 1.5f;  // ダッシュ加速量
        heroBaseStatus.maxDushSpeed       = 10.5f; // 最大ダッシュ速度
        heroBaseStatus.traction           = 0.9f;  // 地上抵抗
        heroBaseStatus.airAcceleration    = 5.0f;  // 空中加速
        heroBaseStatus.maxAirSpeed        = 1.0f;  // 空中最大速度
        heroBaseStatus.airFriction        = 4.0f;  // 空中抵抗
        heroBaseStatus.maxFallSpeed       = 3.0f;  // 最大落下速度
        heroBaseStatus.fastFallSpeed      = 5.0f;  // 急降下速度
        heroBaseStatus.fullJumpVelocity   = 9.0f;  // 大ジャンプ初速度
        heroBaseStatus.shortJumpVelocity  = 4.0f;  // 小ジャンプ初速度
        heroBaseStatus.doubleJumpVelocity = 9.0f;  // 2段ジャンプ初速度
    } break;
    case BeyType::Snowflake: {
        heroBaseStatus.mass               = 50.0f; // 質量
        heroBaseStatus.walkAcceleration   = 4.0f;  // 歩行加速
        heroBaseStatus.maxWalkSpeed       = 4.0f;  // 最大歩行スピード
        heroBaseStatus.initialDushSpeed   = 3.0f;  // ダッシュ初速度
        heroBaseStatus.dushAcceleration   = 1.5f;  // ダッシュ加速量
        heroBaseStatus.maxDushSpeed       = 10.5f; // 最大ダッシュ速度
        heroBaseStatus.traction           = 0.9f;  // 地上抵抗
        heroBaseStatus.airAcceleration    = 5.0f;  // 空中加速
        heroBaseStatus.maxAirSpeed        = 1.0f;  // 空中最大速度
        heroBaseStatus.airFriction        = 4.0f;  // 空中抵抗
        heroBaseStatus.maxFallSpeed       = 3.0f;  // 最大落下速度
        heroBaseStatus.fastFallSpeed      = 5.0f;  // 急降下速度
        heroBaseStatus.fullJumpVelocity   = 9.0f;  // 大ジャンプ初速度
        heroBaseStatus.shortJumpVelocity  = 4.0f;  // 小ジャンプ初速度
        heroBaseStatus.doubleJumpVelocity = 9.0f;  // 2段ジャンプ初速
    } break;
    default:
        std::cout << "BeyType error Hero" << std::endl;
        break;
    }
    mBaseStatus = heroBaseStatus;

    // RigidBody setting
    Physics* physics      = SceneManager::GetCurrentScene()->GetPhysics();
    RigidBody* rigidBody  = new RigidBody(this, rp3d::BodyType::DYNAMIC, physics);
    rp3d::RigidBody* rprb = rigidBody->GetRp3dRogidBody();
    rprb->setMass(mBaseStatus.mass);
    rprb->setAngularLockAxisFactor(rp3d::Vector3(0, 0, 0));

    // collider(hero body)
    reactphysics3d::decimal radius = 1.5f; // 半径
    // reactphysics3d::decimal height = 0.9f; // 高さ
    rp3d::Vector3 position(0.0, radius, 0.0);
    rp3d::Quaternion rotation(rp3d::Quaternion::identity()); // 回転なし
    rp3d::Transform offset(position, rotation);

    rp3d::CollisionShape* shape = physics->GetPhysicsCommon().createSphereShape(radius);
    rp3d::Collider* collider1   = rprb->addCollider(shape, offset);
    collider1->getMaterial().setFrictionCoefficient(mBaseStatus.traction);
    collider1->getMaterial().setBounciness(0.0f);

    // collider(foot)
    radius   = 0.05f;
    position = rp3d::Vector3(0.0f, radius, 0.0f);
    offset   = rp3d::Transform(position, rotation);

    shape                     = physics->GetPhysicsCommon().createSphereShape(radius);
    rp3d::Collider* collider2 = rprb->addCollider(shape, offset);
    collider2->setIsTrigger(true);

    // add component
    AddComponent(rigidBody);

    // behaviour
    SetBehaviour(new HeroMove(this));
    // heroBody, rider, bey

    mHeroBody->GetTransform()->SetLocalPosition(Vector3(0.0f, 1.0f, 0.0f));
    mHeroBody->GetTransform()->SetParent(GetTransform(), false);

    mRider->GetTransform()->SetParent(mHeroBody->GetTransform(), false);

    mBey->GetTransform()->SetParent(mHeroBody->GetTransform(), false);
}