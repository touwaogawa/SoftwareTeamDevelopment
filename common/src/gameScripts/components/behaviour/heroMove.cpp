#include "heroMove.h"
#include "../../../../../utils/src/math.h"
#include "../../../component/rigidBody.h"
#include "../../../component/transform.h"
#include "../../gameObject/hero.h"
#include "../../gameObject/hitBox.h"
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

    // if (mTransform->GetParent()) {
    //     std::cout << "Hero has pa from Heromove mTransform" << std::endl;
    // }
    // if (mOwner->GetTransform()->GetParent()) {
    //     std::cout << "Hero has pa ffrom Heromove mOwner Gettrans" << std::endl;
    // }
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
        Vector2 v = mHero->mCurrentStatus.velocity;
        mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(v.x, vel.y, v.y));
    } break;
    case HeroState::Running: {
        Vector2 v = mHero->mCurrentStatus.velocity;
        mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(v.x, vel.y, v.y));
    } break;
    case HeroState::PreRunningAttack: {

        if (mHero->mCurrentStatus.actionFrame >= 5) {
            mHero->SetState(HeroState::RunningAttack);
        }
    } break;
    case HeroState::RunningAttack: {
        int attackTime = 20;
        if (mHero->mCurrentStatus.actionFrame == 0 && mHero->mCurrentStatus.stopFrame < 0) {
            float x        = mHero->mCurrentStatus.faceDir.x * 7.5f;
            float y        = mHero->mCurrentStatus.faceDir.y * 7.5f;
            HitBox* hitBox = new HitBox(mHero, mHero->GetTag(), 1.7f, Vector3(x, 12.0f, y), 10.0f, attackTime, mHero->mCurrentStatus.actionFrame);
            hitBox->GetTransform()->SetLocalPosition(Vector3(0.0f, 1.7f, 0.0f));
            hitBox->GetTransform()->SetParent(GetTransform(), false);
        }
        if (mHero->mCurrentStatus.actionFrame < attackTime) {
            float x = mHero->mCurrentStatus.faceDir.x * 20.0f;
            float y = mHero->mCurrentStatus.faceDir.y * 20.0f;
            mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(x, 0.0, y));
        } else {

            mHero->SetState(HeroState::AfterRunningAttack);
        }
    } break;
    case HeroState::AfterRunningAttack: {
        if (mHero->mCurrentStatus.actionFrame >= 5) {
            mHero->SetState(HeroState::Idle);
        }
    } break;
    case HeroState::PreFallAttack: {

    } break;
    case HeroState::FallAttack: {

    } break;
    case HeroState::AfterFallAttack: {

    } break;
    case HeroState::PreAirFrontAttack: {

    } break;
    case HeroState::AirFrontAttack: {

    } break;
    case HeroState::AfterAirFrontAttack: {

    } break;
    case HeroState::PreAirBackAttack: {

    } break;
    case HeroState::AirBackAttack: {

    } break;
    case HeroState::AfterAirBackAttack: {

    } break;
    case HeroState::PreJump: {
        if (mHero->mCurrentStatus.actionFrame < 2) {
            GetTransform()->SetLocalScale(Vector3(1.0f, 1.0f - (mHero->mCurrentStatus.actionFrame * 0.1f), 1.0f));
        }
        if (mHero->mCurrentStatus.actionFrame == 2) {
            GetTransform()->SetLocalScale(Vector3(1.0f, 1.0f, 1.0f));
        }
    } break;
    case HeroState::BigJump: {

        mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(vel.x, mHero->GetBaseStatus().fullJumpVelocity, vel.z));
        mHero->SetState(HeroState::AirIdle);
    } break;
    case HeroState::SmallJump: {

        mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(vel.x, mHero->GetBaseStatus().shortJumpVelocity, vel.z));
        mHero->SetState(HeroState::AirIdle);
    } break;
    case HeroState::AirIdle: {
    } break;
    case HeroState::AirMove: {
        Vector2 v = mHero->mCurrentStatus.velocity;
        mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(v.x, vel.y, v.y));

    } break;
    case HeroState::AirPreJump: {
        mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(vel.x, mHero->GetBaseStatus().doubleJumpVelocity, vel.z));
        mHero->SetState(HeroState::AirIdle);
        mHero->mCurrentStatus.airJumpCount++;

    } break;
    case HeroState::KnockBack: {
        if (mHero->mCurrentStatus.actionFrame == 0) {
        } else if (mHero->mCurrentStatus.actionFrame == 1) {
            mHeroRp3dRigidBody->setLinearVelocity(mKnockBackVectorBuffer);
        } else {
        }
        if (0 < mHero->mCurrentStatus.downFrame) {
        } else {
            mHero->SetState(HeroState::Idle);
        }
    } break;
    case HeroState::Death: {
        // std::cout << "Death" << std::endl;
        mHero->GetPlayer()->SetPlayerState(PlayerState::Defeat);
    } break;
    default:
        std::cout << "Update HeroState error" << std::endl;
        break;
    }

    // 常時処理##############################
    if (mHero->mCurrentStatus.stopFrame > 0) {
        mHero->mCurrentStatus.stopFrame--;
        if (mHeroRp3dRigidBody->getType() == rp3d::BodyType::DYNAMIC) {
            mHeroRp3dRigidBody->setType(rp3d::BodyType::KINEMATIC);
        }
    } else if (mHero->mCurrentStatus.stopFrame == 0) {
        if (mHeroRp3dRigidBody->getType() == rp3d::BodyType::KINEMATIC) {
            mHeroRp3dRigidBody->setType(rp3d::BodyType::DYNAMIC);
        }

        mHeroRp3dRigidBody->setLinearVelocity(mKnockBackVectorBuffer);
        mHero->mCurrentStatus.stopFrame--;
    } else {
        mHero->mCurrentStatus.actionFrame++;
        if (mHero->mCurrentStatus.downFrame > 0) {
            mHero->mCurrentStatus.downFrame--;
        }
    }
    // std::cout << "action: " << mHero->mCurrentStatus.actionFrame << std::endl;
    // std::cout << "stop: " << mHero->mCurrentStatus.stopFrame << std::endl;
    // std::cout << "down: " << mHero->mCurrentStatus.downFrame << std::endl;
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
    case HeroState::Running: {
    } break;
    case HeroState::RunningAttack: {
    } break;
    case HeroState::PreJump: {
    } break;
    case HeroState::AirIdle:
    case HeroState::AirMove: {
    } break;
    case HeroState::KnockBack: {
        if (op->GetName() == "Stage") {
            // std::cout << "on enter stage!!" << std::endl;
            mHero->mCurrentStatus.airJumpCount = 0;
            mHero->SetState(HeroState::Idle);
        }
    } break;
    case HeroState::Death: {
    } break;
    default:
        // std::cout << "OnCollisionEnter HeroState error" << std::endl;
        break;
    }
}
void HeroMove::OnCollisionExit(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::CollisionCallback::ContactPair& pair)
{
    // GameObject* op = static_cast<GameObject*>(opponent->getBody()->getUserData());
    switch (mHero->mCurrentStatus.state) {
    case HeroState::Idle:
    case HeroState::Walking:
    case HeroState::Running:
    case HeroState::RunningAttack:
    case HeroState::PreJump: {
    } break;
    case HeroState::AirIdle:
    case HeroState::AirMove: {
    } break;
    case HeroState::KnockBack: {
    } break;
    case HeroState::Death: {
    } break;
    default:
        // std::cout << "OnCollisionEnter HeroState error" << std::endl;
        break;
    }
}

void HeroMove::OnOverlapEnter(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::OverlapCallback::OverlapPair& pair)
{
    GameObject* op = static_cast<GameObject*>(opponent->getBody()->getUserData());
    switch (mHero->mCurrentStatus.state) {
    case HeroState::Idle: {
    } break;
    case HeroState::Walking: {
    } break;
    case HeroState::Running: {
    } break;
    case HeroState::RunningAttack: {

    } break;
    case HeroState::PreJump: {
    } break;
    case HeroState::AirIdle:
    case HeroState::AirMove: {
        if (op->GetName() == "Stage") {
            // std::cout << "on enter stage!!" << std::endl;
            mHero->mCurrentStatus.airJumpCount = 0;
            if (mHero->mCurrentStatus.velocity.Length() > 0) {
                mHero->SetState(HeroState::Running);
            } else {
                mHero->SetState(HeroState::Idle);
            }
        }
    } break;
    case HeroState::KnockBack: {
    } break;
    case HeroState::Death: {
    } break;
    default:
        // std::cout << "OnOverlapEnter HeroState error" << std::endl;
        break;
    }
}
void HeroMove::OnOverlapExit(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::OverlapCallback::OverlapPair& pair)
{
    GameObject* op = static_cast<GameObject*>(opponent->getBody()->getUserData());
    switch (mHero->mCurrentStatus.state) {
    case HeroState::Idle:
    case HeroState::Walking:
    case HeroState::Running:
    case HeroState::RunningAttack:
        if (op->GetName() == "Stage") {
            // std::cout << "on exit stage!!" << std::endl;
            if (mHero->mCurrentStatus.velocity.Length() > 0) {
                mHero->SetState(HeroState::AirMove);
            } else {
                mHero->SetState(HeroState::AirIdle);
            }
        }
        break;
    case HeroState::PreJump: {
    } break;
    case HeroState::AirIdle:
    case HeroState::AirMove: {
    } break;
    case HeroState::KnockBack: {
    } break;
    case HeroState::Death: {
    } break;
    default:
        // std::cout << "OnCollisionEnter HeroState error" << std::endl;
        break;
    }

    if (mHero->mCurrentStatus.state != HeroState::Death) {
        if (op->GetName() == "SafeArea") {
            mHero->SetState(HeroState::Death);
        }
    }
}

void HeroMove::OnDamage(int stopFrame, int downFrame, rp3d::Vector3 vector)
{
    std::cout << "on damage stopframe: " << stopFrame << std::endl;
    mHero->mCurrentStatus.stopFrame = stopFrame;
    mKnockBackVectorBuffer          = vector;
    mHero->mCurrentStatus.downFrame = downFrame;
    mHero->SetState(HeroState::KnockBack);
}

void HeroMove::HitOther(int stopFrame, float power)
{
    std::cout << "hit other stopframe: " << stopFrame << std::endl;
    mHero->mCurrentStatus.stopFrame = stopFrame;
    mKnockBackVectorBuffer          = mHeroRp3dRigidBody->getLinearVelocity();
}