#include "heroMove.h"
#include "../../../../../utils/src/math.h"
#include "../../../component/rigidBody.h"
#include "../../../component/transform.h"
#include "../../gameObject/hero.h"
#include "../../gameObject/player.h"
#include <iostream>
HeroMove::HeroMove(Hero* owner)
    : Behaviour(owner)
    , mHero(owner)
{
    // std::cout << "heroMove constructor" << std::endl;
}

void HeroMove::Start()
{
    // std::cout << "heroMove start" << std::endl;
    RigidBody* r = mOwner->GetComponent<RigidBody>();
    if (r) {
        r->SetTransform();
        mHeroRp3dRigidBody = r->GetRp3dRogidBody();
        if (!mHeroRp3dRigidBody) {
            std::cout << "rp3d rigid body error hero move start()" << std::endl;
        }
    } else {
        std::cout << "rigid body error hero move start()" << std::endl;
    }
}
namespace {
// デバッグ用
void show(Transform* transform)
{
    std::cout << "heromove" << std::endl;
    Quaternion wq = transform->GetWorldRotation();
    std::cout << " wqx:" << wq.x << " wqy:" << wq.y << " wqz:" << wq.z << " wqw:" << wq.w << std::endl;
    Quaternion lq = transform->GetLocalRotation();
    std::cout << " lqx:" << lq.x << " lqy:" << lq.y << " lqz:" << lq.z << " lqw:" << lq.w << std::endl;
    Vector3 wpos = transform->GetWorldPosition();
    std::cout << " wposx:" << wpos.x << " wposy:" << wpos.y << " wposz:" << wpos.z << std::endl;
    Vector3 lpos = transform->GetLocalPosition();
    std::cout << " lposx:" << lpos.x << " lposy:" << lpos.y << " lposz:" << lpos.z << std::endl;
    Vector3 wscale = transform->GetWorldScale();
    std::cout << " wscalex:" << wscale.x << " wscaley:" << wscale.y << " wscalez:" << wscale.z << std::endl;
    Vector3 lscale = transform->GetLocalScale();
    std::cout << " lscalex:" << lscale.x << " lscaley:" << lscale.y << " lscalez:" << lscale.z << std::endl;
    if (transform->GetParent() == nullptr)
        std::cout << "noparent" << std::endl;
}

}
void HeroMove::Update()
{
    // show(mOwner->GetTransform());
    switch (mHero->mCurrentStatus.state) {
    case HeroState::Idle: {
    } break;
    case HeroState::Walking: {
        float x = mHero->mCurrentStatus.moveDir.x * mHero->GetBaseStatus().WalkSpeed;
        float y = mHero->mCurrentStatus.moveDir.y * mHero->GetBaseStatus().WalkSpeed;
        mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(x, 0.0, y));
    } break;
    case HeroState::StartRunning: {
        float x = mHero->mCurrentStatus.moveDir.x * mHero->GetBaseStatus().initialDushSpeed;
        float y = mHero->mCurrentStatus.moveDir.y * mHero->GetBaseStatus().initialDushSpeed;
        mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(x, 0.0, y));
        mHero->mCurrentStatus.state = HeroState::Running;
    } break;
    case HeroState::Running: {
        float x = mHero->mCurrentStatus.moveDir.x * mHero->GetBaseStatus().dushAcceleration;
        float y = mHero->mCurrentStatus.moveDir.y * mHero->GetBaseStatus().dushAcceleration;
        mHeroRp3dRigidBody->applyWorldForceAtCenterOfMass(rp3d::Vector3(x, 0.0, y) * mHero->GetBaseStatus().mass);
        if (mHeroRp3dRigidBody->getLinearVelocity().length() <= mHero->GetBaseStatus().maxDushSpeed) {
        } else {
            float x = mHero->mCurrentStatus.moveDir.x * mHero->GetBaseStatus().maxDushSpeed;
            float y = mHero->mCurrentStatus.moveDir.y * mHero->GetBaseStatus().maxDushSpeed;
            mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(x, 0.0, y));
        }
    } break;
    case HeroState::StopRunning: {
        if (mHeroRp3dRigidBody->getLinearVelocity().length() < mHero->GetBaseStatus().initialDushSpeed) {
            mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(0.0, 0.0, 0.0));
            mHero->mCurrentStatus.state = HeroState::Idle;
        }
    } break;
    case HeroState::RunningAttack: {
    } break;
    case HeroState::PreJump: {
        if (mHero->mActionFrame >= 3) {
        }
    } break;
    case HeroState::AirIdle: {
    } break;
    case HeroState::Death: {
    } break;
    default:
        std::cout << "HeroState error" << std::endl;
        break;
    }

    if (mHero->mStopFrame) {
        mHero->mStopFrame--;
    } else {
        mHero->mActionFrame++;
    }

    if (mTransform->GetWorldPosition().y < -20.0f) {
        mHero->GetPlayer()->SetPlayerState(PlayerState::Defeat);
        mHero->mCurrentStatus.state = HeroState::Death;
    }
    // std::cout << "y: " << mHeroRp3dRigidBody->getTransform().getPosition().y << std::endl;
}
void HeroMove::LateUpdate()
{
}

// ##############################################

void HeroMove::OnCollisionEnter(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::CollisionCallback::ContactPair& pair)
{
    // std::cout << "on col hero move" << std::endl;
}

void HeroMove::OnOverlapEnter(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::OverlapCallback::OverlapPair& pair)
{
    // std::cout << "on overlap hero move" << std::endl;
}