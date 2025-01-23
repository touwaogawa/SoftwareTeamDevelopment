#include "heroMove.h"
#include "../../../../../common/src/component/rigidBody.h"
#include "../../../../../common/src/component/transform.h"
#include "../../../../../utils/src/math.h"
#include "../../../audio.h"
#include "../../../renderer.h"
#include "../../gameObject/effect/jumpCircleEffect.h"
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

        if (mHero->mCurrentStatus.actionFrame >= 20) {
            mHero->SetState(HeroState::RunningAttack);
        }
    } break;
    case HeroState::RunningAttack: {
        int attackTime = 20;
        if (mHero->mCurrentStatus.stopFrame < 0) {
            if (mHero->mCurrentStatus.actionFrame == 0) {
                float x        = mHero->mCurrentStatus.faceDir.x * 14.5f;
                float y        = mHero->mCurrentStatus.faceDir.y * 14.5f;
                HitBox* hitBox = new HitBox(mHero, mHero->GetTag(), 1.7f, Vector3(x, 10.0f, y), 10.0f, attackTime, mHero->mCurrentStatus.actionFrame);
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
        }
    } break;
    case HeroState::AfterRunningAttack: {
        if (mHero->mCurrentStatus.actionFrame >= 25) {
            mHero->SetState(HeroState::Idle);
            // std::cout << "AfterRunningAttack -> idle" << std::endl;

            break;
        }
    } break;
    case HeroState::PreFallAttack: {
        if (mHero->mCurrentStatus.stopFrame < 0) {
            mHero->SetState(HeroState::FallAttack);
        }
    } break;
    case HeroState::FallAttack: {
        if (mHero->mCurrentStatus.stopFrame < 0) {
            if (mHero->mCurrentStatus.actionFrame == 0) {
                mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(0.0f, -13.0f, 0.0f));
                HitBox* hitBox = new HitBox(mHero, mHero->GetTag(), 1.0f, Vector3(0.0f, -1.0f, 0.0f), 3.5f, 15, mHero->mCurrentStatus.actionFrame);
                hitBox->GetTransform()->SetLocalPosition(Vector3(0.0f, 0.5f, 0.0f));
                hitBox->GetTransform()->SetParent(GetTransform(), false);
            } else if (mHero->mCurrentStatus.actionFrame < 150) {
                if (mHero->mCurrentStatus.onGround) {
                    mHero->SetState(HeroState::AfterFallAttack);
                }
                if (mHero->mCurrentStatus.actionFrame % 20 == 0) {
                    HitBox* hitBox = new HitBox(mHero, mHero->GetTag(), 1.0f, Vector3(0.0f, -1.0f, 0.0f), 3.5f, 7, mHero->mCurrentStatus.actionFrame);
                    hitBox->GetTransform()->SetLocalPosition(Vector3(0.0f, 0.5f, 0.0f));
                    hitBox->GetTransform()->SetParent(GetTransform(), false);
                }
            } else {
                mHero->SetState(HeroState::AfterFallAttack);
                break;
            }
        }
    } break;
    case HeroState::AfterFallAttack: {
        if (mHero->mCurrentStatus.stopFrame < 0) {
            if (mHero->mCurrentStatus.actionFrame == 10) {
                if (mHero->mCurrentStatus.onGround) {
                    mHero->SetState(HeroState::Idle);
                } else {
                    mHero->SetState(HeroState::AirIdle);
                }
            }
        }
    } break;
    case HeroState::PreAirFrontAttack: {
        if (mHero->mCurrentStatus.stopFrame < 0) {
            mHero->SetState(HeroState::AirFrontAttack);
        }
    } break;
    case HeroState::AirFrontAttack: {
        if (mHero->mCurrentStatus.stopFrame < 0) {
            if (mHero->mCurrentStatus.actionFrame == 0) {
                mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(vel.x, 1.0f, vel.z));
            }
            if (mHero->mCurrentStatus.actionFrame == 15) {
                HitBox* hitBox = new HitBox(mHero, mHero->GetTag(), 1.4f, Vector3(0.0f, -4.0f, 0.0f), 4.5f, 12, mHero->mCurrentStatus.actionFrame);
                hitBox->GetTransform()->SetLocalPosition(Vector3(0.0f, -0.5f, 0.0f));
                hitBox->GetTransform()->SetParent(mHero->GetBey()->GetTransform(), false);
            }
            if (mHero->mCurrentStatus.actionFrame == 20) {
                mHero->SetState(HeroState::AfterAirFrontAttack);
            }
        }
    } break;
    case HeroState::AfterAirFrontAttack: {
        if (mHero->mCurrentStatus.stopFrame < 0) {
            if (mHero->mCurrentStatus.actionFrame == 4) {
                if (mHero->mCurrentStatus.onGround) {
                    mHero->SetState(HeroState::Idle);
                } else {
                    mHero->SetState(HeroState::AirIdle);
                }
            }
        }
    } break;
    case HeroState::PreAirBackAttack: {
        if (mHero->mCurrentStatus.stopFrame < 0) {
            mHero->SetState(HeroState::AirBackAttack);
        }
    } break;
    case HeroState::AirBackAttack: {
        if (mHero->mCurrentStatus.stopFrame < 0) {
            if (mHero->mCurrentStatus.actionFrame == 0) {
                mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(vel.x, 1.0f, vel.z));
            }
            if (mHero->mCurrentStatus.actionFrame == 6) {
                float x        = -mHero->mCurrentStatus.faceDir.x * 8.5f;
                float y        = -mHero->mCurrentStatus.faceDir.y * 8.5f;
                HitBox* hitBox = new HitBox(mHero, mHero->GetTag(), 1.2f, Vector3(x, 3.0f, y), 2.5f, 10.5, mHero->mCurrentStatus.actionFrame);
                hitBox->GetTransform()->SetLocalPosition(Vector3(0.0f, 0.0f, 0.0f));
                hitBox->GetTransform()->SetParent(mHero->GetBey()->GetTransform(), false);

                hitBox = new HitBox(mHero, mHero->GetTag(), 0.5f, Vector3(x, 3.0f, y), 2.5f, 10.5, mHero->mCurrentStatus.actionFrame);
                hitBox->GetTransform()->SetLocalPosition(Vector3(0.0f, -0.7f, 0.0f));
                hitBox->GetTransform()->SetParent(mHero->GetBey()->GetTransform(), false);
            }
            if (mHero->mCurrentStatus.actionFrame == 12) {
                mHero->SetState(HeroState::AfterAirBackAttack);
            }
        }
    } break;
    case HeroState::AfterAirBackAttack: {
        if (mHero->mCurrentStatus.stopFrame < 0) {
            if (mHero->mCurrentStatus.actionFrame == 4) {
                if (mHero->mCurrentStatus.onGround) {
                    mHero->SetState(HeroState::Idle);
                } else {
                    mHero->SetState(HeroState::AirIdle);
                }
            }
        }
    } break;
    case HeroState::PreJump: {
    } break;
    case HeroState::BigJump: {
        if (mHero->mCurrentStatus.stopFrame < 0) {
            if (mHero->mCurrentStatus.actionFrame == 0) {
                new JumpCircleEffect(GetTransform()->GetWorldPosition());
                Audio::PlayChunk("../assets/sounds/se/「とう！」.mp3");
                mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(vel.x, mHero->GetBaseStatus().fullJumpVelocity, vel.z));
            } else if (mHero->mCurrentStatus.actionFrame < 4) {

            } else if ((mHero->mCurrentStatus.actionFrame == 4)) {
                mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(vel.x, vel.y * 0.7f, vel.z));
                if (mHero->mCurrentStatus.velocity.LengthSq() > 0) {
                    mHero->SetState(HeroState::AirMove);
                } else {
                    mHero->SetState(HeroState::AirIdle);
                }
            }
        }
    } break;
    case HeroState::SmallJump: {
        if (mHero->mCurrentStatus.stopFrame < 0) {

            new JumpCircleEffect(GetTransform()->GetWorldPosition());
            Audio::PlayChunk("../assets/sounds/se/「とう！」.mp3");
            mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(vel.x, mHero->GetBaseStatus().shortJumpVelocity, vel.z));
            if (mHero->mCurrentStatus.velocity.LengthSq() > 0) {
                mHero->SetState(HeroState::AirMove);
                break;
            } else {
                mHero->SetState(HeroState::AirIdle);
                break;
            }
        }
    } break;
    case HeroState::AirIdle: {
        if (mHero->mCurrentStatus.onGround) {
            // std::cout << "airidle -> idle" << std::endl;
            if (mHero->mCurrentStatus.actionFrame > 0) {
                mHero->SetState(HeroState::Idle);
                break;
            }
        }
    } break;
    case HeroState::AirMove: {
        if (mHero->mCurrentStatus.stopFrame < 0) {
            Vector2 v = mHero->mCurrentStatus.velocity;
            mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(v.x, vel.y, v.y));
            if (mHero->mCurrentStatus.onGround) {
                if (mHero->mCurrentStatus.actionFrame > 0) {
                    mHero->SetState(HeroState::Running);
                    break;
                }
            }
        }
    } break;
    case HeroState::AirPreJump: {
        if (mHero->mCurrentStatus.stopFrame < 0) {
            new JumpCircleEffect(GetTransform()->GetWorldPosition());
            Audio::PlayChunk("../assets/sounds/se/「とう！」.mp3");
            mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(vel.x, mHero->GetBaseStatus().doubleJumpVelocity, vel.z));
            mHero->mCurrentStatus.airJumpCount++;
            mHero->SetState(HeroState::AirIdle);
            break;
        }
    } break;
    case HeroState::KnockBack: {
        if (mHero->mCurrentStatus.stopFrame < 0) {
            if (mHero->mCurrentStatus.actionFrame == 0) {
                mHeroRp3dRigidBody->setLinearVelocity(mKnockBackVectorBuffer);
            }
            if (mHero->mCurrentStatus.knockbackTime == 6) {
                rp3d::Vector3 minimizedVec = mHeroRp3dRigidBody->getLinearVelocity();
                minimizedVec.normalize();
                minimizedVec *= 3.0f;
                mHeroRp3dRigidBody->setLinearVelocity(minimizedVec);
            }
            if (mHero->mCurrentStatus.knockbackTime <= 0) {

                if (mHero->mCurrentStatus.onGround) {
                    mHero->SetState(HeroState::Idle);
                    break;
                } else {
                    mHero->SetState(HeroState::AirIdle);
                    break;
                }
            }
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
        if (mHero->mCurrentStatus.knockbackTime > 0) {
            mHero->mCurrentStatus.knockbackTime--;
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
    } break;
    case HeroState::KnockBack: {
    } break;
    case HeroState::Death: {
    } break;
    default:
        // std::cout << "OnOverlapEnter HeroState error" << std::endl;
        break;
    }
    if (op->GetName() == "Stage") {
        // std::cout << "on overlap enter stage!!" << std::endl;
        mHero->mCurrentStatus.airJumpCount = 0;
        mHero->mCurrentStatus.onGround     = true;
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

    if (op->GetName() == "Stage") {
        // std::cout << "on overlap exit stage!!" << std::endl;
        mHero->mCurrentStatus.onGround = false;
    }

    if (mHero->mCurrentStatus.state != HeroState::Death) {
        if (op->GetName() == "SafeArea") {
            mHero->SetState(HeroState::Death);
        }
    }
}

void HeroMove::OnDamage(float damage, int stopFrame, int knockbackTime, rp3d::Vector3 vector)
{
    // std::cout << "on damage stopframe: " << stopFrame << std::endl;
    mKnockBackVectorBuffer              = vector;
    mHero->mCurrentStatus.stopFrame     = stopFrame;
    mHero->mCurrentStatus.knockbackTime = knockbackTime;
    mHero->mCurrentStatus.damageSum += damage;
    mHero->SetState(HeroState::KnockBack);
    float vectorPower = vector.lengthSquare();
    if (vectorPower < 40 * 40) {
        Audio::PlayChunk("../assets/sounds/se/軽いキック1.mp3");

    } else if (vectorPower < 70 * 70) {
        Audio::PlayChunk("../assets/sounds/se/重いパンチ1.mp3");

    } else {
        Audio::PlayChunk("../assets/sounds/se/重いパンチ2.mp3");
        Audio::PlayChunk("../assets/sounds/se/金属バットで打つ1.mp3");
        Audio::PlayChunk("../assets/sounds/se/「ぐああっ！」.mp3");
    }
    Renderer::CameraShakeStart(stopFrame / 2, vectorPower);
}

void HeroMove::HitOther(int stopFrame)
{
    // std::cout << "hit other stopframe: " << stopFrame << std::endl;
    mHero->mCurrentStatus.stopFrame = stopFrame;
    mKnockBackVectorBuffer          = mHeroRp3dRigidBody->getLinearVelocity();
}