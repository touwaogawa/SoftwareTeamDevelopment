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
    , mKnockBackVectorBuffer(rp3d::Vector3(0.0f, 0.0f, 0.0f))
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
    // std::cout << "a : " << mHero->GetBaseStatus().airMoveSpeed << std::endl;
    // std::cout << "a : " << mHero->GetBaseStatus().attackSpeed << std::endl;
    // std::cout << "b : " << mHero->GetBaseStatus().bigJumpVelocity << std::endl;
    // std::cout << "d : " << mHero->GetBaseStatus().dushAcceleration << std::endl;
    // std::cout << "i : " << mHero->GetBaseStatus().initialDushSpeed << std::endl;
    // std::cout << "m : " << mHero->GetBaseStatus().mass << std::endl;
    // std::cout << "m : " << mHero->GetBaseStatus().maxDushSpeed << std::endl;
    // std::cout << "s : " << mHero->GetBaseStatus().smallJumpVelocity << std::endl;
    // std::cout << "t : " << mHero->GetBaseStatus().traction << std::endl;
    // std::cout << "w : " << mHero->GetBaseStatus().WalkSpeed << std::endl;

    rp3d::Vector3 vel = mHeroRp3dRigidBody->getLinearVelocity();
    switch (mHero->mCurrentStatus.state) {
    case HeroState::Idle: {
        // rp3d::Vector3 vel = mHeroRp3dRigidBody->getLinearVelocity();
        // if (vel.length() < 0.5) {
        //     mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(0.0, 0.0, 0.0));
        // } else {
        //     mHeroRp3dRigidBody->applyWorldForceAtCenterOfMass(-vel * 1.5);
        // }
    } break;
    case HeroState::Walking: {
        float x = mHero->mCurrentStatus.moveDir.x * mHero->GetBaseStatus().WalkSpeed;
        float y = mHero->mCurrentStatus.moveDir.y * mHero->GetBaseStatus().WalkSpeed;
        mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(x, vel.y, y));
    } break;
    case HeroState::StartRunning: {
        float x = mHero->mCurrentStatus.moveDir.x * mHero->GetBaseStatus().initialDushSpeed;
        float y = mHero->mCurrentStatus.moveDir.y * mHero->GetBaseStatus().initialDushSpeed;
        mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(x, vel.y, y));
        mHero->SetState(HeroState::Running);
    } break;
    case HeroState::Running: {
        float x = mHero->mCurrentStatus.moveDir.x * mHero->GetBaseStatus().maxDushSpeed;
        float y = mHero->mCurrentStatus.moveDir.y * mHero->GetBaseStatus().maxDushSpeed;
        mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(x, vel.y, y));
    } break;
    case HeroState::StopRunning: {
        if (mHeroRp3dRigidBody->getLinearVelocity().length() < mHero->GetBaseStatus().initialDushSpeed) {
            mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(0.0, 0.0, 0.0));
            mHero->SetState(HeroState::Idle);
        } else {
            // 減速
            mHeroRp3dRigidBody->applyWorldForceAtCenterOfMass(-mHeroRp3dRigidBody->getLinearVelocity());
        }
    } break;
    case HeroState::RunningAttack: {
        if (mHero->mActionFrame < 40) {
            float x = mHero->mCurrentStatus.faceDir.x * mHero->GetBaseStatus().attackSpeed;
            float y = mHero->mCurrentStatus.faceDir.y * mHero->GetBaseStatus().attackSpeed;
            mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(x, 0.0, y));
        } else {
            mHero->SetState(HeroState::Idle);
        }
    } break;
    case HeroState::PreJump: {
        // if (mHero->mActionFrame < 2) {
        //     mTransform->SetLocalScale(Vector3(1.0f, 1.0f - (mHero->mActionFrame * 0.1f), 1.0f));
        // }
        // if (mHero->mActionFrame == 2) {
        //     mTransform->SetLocalScale(Vector3(1.0f, 1.0f, 1.0f));
        // }
    } break;
    case HeroState::BigJump: {
        // mHeroRp3dRigidBody->applyLocalForceAtCenterOfMass(rp3d::Vector3(0.0, mHero->GetBaseStatus().bigJumpVelocity, 0.0));
        // mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(vel.x, mHero->GetBaseStatus().bigJumpVelocity, vel.z));
        mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(vel.x, 6.0, vel.z));
        mHero->SetState(HeroState::AirIdle);
    } break;
    case HeroState::SmallJump: {
        // mHeroRp3dRigidBody->applyWorldForceAtCenterOfMass(rp3d::Vector3(0.0, mHero->GetBaseStatus().smallJumpVelocity, 0.0));
        // mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(vel.x, mHero->GetBaseStatus().smallJumpVelocity, vel.z));
        mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(vel.x, 3.0, vel.z));
        mHero->SetState(HeroState::AirIdle);
    } break;
    case HeroState::AirIdle: {
        float x = mHero->mCurrentStatus.moveDir.x * mHero->GetBaseStatus().airMoveSpeed;
        float y = mHero->mCurrentStatus.moveDir.y * mHero->GetBaseStatus().airMoveSpeed;
        mHeroRp3dRigidBody->applyWorldForceAtCenterOfMass(rp3d::Vector3(x, 0.0, y));
        // mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(x, vel.y, y));
    } break;
    case HeroState::KnockBack: {
        if (mHero->mActionFrame == 2) {
            mHeroRp3dRigidBody->setLinearVelocity(mKnockBackVectorBuffer);
        }
        if (mHero->mActionFrame >= mHero->mDownFrame) {
            mHero->SetState(HeroState::Idle);
        }
    } break;
    case HeroState::Death: {
        // std::cout << "Death" << std::endl;
        mHero->GetPlayer()->SetPlayerState(PlayerState::Defeat);
    } break;
    default:
        std::cout << "HeroState error" << std::endl;
        break;
    }

    // 常時処理##############################
    if (mHero->mStopFrame > 0) {
        mHero->mStopFrame--;
    } else if (mHero->mStopFrame == 0) {
        mHeroRp3dRigidBody->setLinearVelocity(mKnockBackVectorBuffer);
        mHero->mStopFrame--;
    } else {
        mHero->mActionFrame++;
    }
    if (mHero->mDownFrame > 0) {
        mHero->mDownFrame--;
    }

    if (mTransform->GetWorldPosition().y < -20.0f) {
        mHero->SetState(HeroState::Death);
        // std::cout << "death" << std::endl;
    }
    // std::cout << "action: " << mHero->mActionFrame << std::endl;
    // std::cout << "stop: " << mHero->mStopFrame << std::endl;
    // std::cout << "down: " << mHero->mDownFrame << std::endl;
}
void HeroMove::LateUpdate()
{
}

// ##############################################

void HeroMove::OnCollisionEnter(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::CollisionCallback::ContactPair& pair)
{
    GameObject* op = static_cast<GameObject*>(opponent->getBody()->getUserData());
    switch (mHero->mCurrentStatus.state) {
    case HeroState::Idle: {
    } break;
    case HeroState::Walking: {
    } break;
    case HeroState::StartRunning: {
    } break;
    case HeroState::Running: {
    } break;
    case HeroState::StopRunning: {
    } break;
    case HeroState::RunningAttack: {
        if (op->GetName() == "Hero") {
            HeroMove* heroMove = static_cast<HeroMove*>(op->GetBehaviour());
            if (heroMove) {
                heroMove->OnDamage(8, 120, mHeroRp3dRigidBody->getLinearVelocity() * 1.2);
            } else {
                std::cout << "static_cast error HeroMove" << std::endl;
            }
        }
    } break;
    case HeroState::PreJump: {
    } break;
    case HeroState::AirIdle: {
        if (op->GetName() == "Stage") {
            std::cout << "stage!!" << std::endl;
            mHero->SetState(HeroState::Idle);
        }
    } break;
    case HeroState::KnockBack: {
    } break;
    case HeroState::HitStop: {
    } break;
    case HeroState::Death: {
    } break;
    default:
        std::cout << "HeroState error" << std::endl;
        break;
    }
}

void HeroMove::OnOverlapEnter(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::OverlapCallback::OverlapPair& pair)
{
    switch (mHero->mCurrentStatus.state) {
    case HeroState::Idle: {
    } break;
    case HeroState::Walking: {
    } break;
    case HeroState::StartRunning: {
    } break;
    case HeroState::Running: {
    } break;
    case HeroState::StopRunning: {
    } break;
    case HeroState::RunningAttack: {
    } break;
    case HeroState::PreJump: {
    } break;
    case HeroState::AirIdle: {
    } break;
    case HeroState::KnockBack: {
    } break;
    case HeroState::HitStop: {
    } break;
    case HeroState::Death: {
    } break;
    default:
        std::cout << "HeroState error" << std::endl;
        break;
    }
}

void HeroMove::OnDamage(int stopFrame, int downFrame, rp3d::Vector3 vector)
{
    mHero->mStopFrame      = stopFrame;
    mKnockBackVectorBuffer = vector;
    mHero->mDownFrame      = downFrame;
    mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(0.0, 0.0, 0.0));
}