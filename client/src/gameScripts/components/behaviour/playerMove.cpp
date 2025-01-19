#include "playerMove.h"
#include "../../../../../common/src/component/transform.h"
#include "../../../../../common/src/scene.h"
#include "../../../../../common/src/sceneManager.h"
#include "../../../../../utils/src/math.h"
#include "../../gameObject/hero.h"
#include "../../gameObject/player.h"
#include "../../gameObject/stage.h"
#include "heroMove.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

PlayerMove::PlayerMove(Player* owner, Hero* hero)
    : Behaviour(owner)
    , mPlayer(owner)
    , mHero(hero)
    , mCommandDelay(0)
    , mMoveAxisNorm(Vector2::Zero)
    , mStickDeadZone(0.1f)
{
}

void PlayerMove::Start()
{
    // std::cout << "playerMove start" << std::endl;
    mHero->SetState(HeroState::Idle);
    GetTransform()->SetWorldRotation(Quaternion::Identity);
    // std::cout << "face dir" << mHero->mCurrentStatus.faceDir.Length() << std::endl;
}
namespace {

}
void PlayerMove::Update()
{
    switch (mPlayer->GetPlayerState()) {
    case PlayerState::Init:
        // std::cout << "init" << std::endl;
        InitUpdate();
        // std::cout << "init_" << std::endl;
        break;
    case PlayerState::Battle:
        // std::cout << "battle" << std::endl;
        BattleUpdate();
        // std::cout << "battle_" << std::endl;
        break;
    case PlayerState::Defeat:
        // std::cout << "defeat" << std::endl;
        DefeatedUpdate();
        // std::cout << "defeat_" << std::endl;
        break;
    default:
        std::cout << "PlayerState error" << std::endl;
        break;
    }
}
void PlayerMove::LateUpdate()
{
}

// ##############################################

void PlayerMove::InitUpdate()
{
}
void PlayerMove::BattleUpdate()
{
    CommandData com    = mPlayer->GetCommandData();
    CommandData preCom = mPlayer->GetPreCommandData();
    mMoveAxisNorm      = com.moveAxis;
    if (mMoveAxisNorm.Length()) {
        mMoveAxisNorm.Normalize();
    }
    switch (mHero->mCurrentStatus.state) {
        // std::cout << "mHero->mCurrentStatus.state" << std::endl;
    case HeroState::Idle:
        // std::cout << "idle" << std::endl;
        if (com.moveAxis.Length() > mStickDeadZone) {
            if (com.moveAxis.Length() - preCom.moveAxis.Length() < 0.3) {
                // 弱く倒す
                mHero->SetState(HeroState::Walking);
            } else {
                // 強く倒す
                mHero->SetState(HeroState::Running);
            }
        }
        if (com.jump && !preCom.jump) {
            mHero->SetState(HeroState::PreJump);
            break;
        }
        break;
    case HeroState::Walking:
        // std::cout << "walk" << std::endl;
        if (com.moveAxis.Length() > mStickDeadZone) {
            if (mMoveAxisNorm.Length() > 0) {
                mHero->mCurrentStatus.faceDir = mMoveAxisNorm;
            }
            Vector2& velocity  = mHero->mCurrentStatus.velocity;
            float maxWalkSpeed = mHero->GetBaseStatus().maxWalkSpeed;

            Vector2 accelerationDir = mMoveAxisNorm * maxWalkSpeed - velocity;
            if (accelerationDir.Length() > 0) {
                velocity += Vector2::Normalize(accelerationDir) * mHero->GetBaseStatus().walkAcceleration;
            }
            if (velocity.Length() > maxWalkSpeed) {
                velocity = Vector2::Normalize(velocity) * maxWalkSpeed;
            }

            if (com.attack1 && !preCom.attack1) {
                mHero->SetState(HeroState::PreRunningAttack);
                break;
            }
            if (com.jump && !preCom.jump) {
                mHero->SetState(HeroState::PreJump);
                break;
            }
        } else {
            mHero->SetState(HeroState::Idle);
            break;
        }
        break;
    case HeroState::Running:
        // std::cout << "running" << std::endl;
        if (com.moveAxis.Length() > mStickDeadZone) {
            if (mMoveAxisNorm.Length() > 0) {
                mHero->mCurrentStatus.faceDir = mMoveAxisNorm;
            }
            Vector2& velocity  = mHero->mCurrentStatus.velocity;
            float maxDushSpeed = mHero->GetBaseStatus().maxDushSpeed;

            Vector2 accelerationDir = mMoveAxisNorm * maxDushSpeed - velocity;
            if (accelerationDir.Length() > 0) {
                velocity += Vector2::Normalize(accelerationDir) * mHero->GetBaseStatus().dushAcceleration;
            }
            if (velocity.Length() > maxDushSpeed) {
                velocity = Vector2::Normalize(velocity) * maxDushSpeed;
            }
            // #################
            if (com.attack1 && !preCom.attack1) {
                mHero->SetState(HeroState::PreRunningAttack);
                break;
            }
            if (com.jump && !preCom.jump) {
                mHero->SetState(HeroState::PreJump);
                break;
            }
        } else {
            mHero->SetState(HeroState::Idle);
        }
        break;
    case HeroState::PreRunningAttack: {
    } break;
    case HeroState::RunningAttack: {
    } break;
    case HeroState::AfterRunningAttack: {
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
        if (mHero->mCurrentStatus.actionFrame >= 3) {
            if (com.jump) {
                // 大ジャンプ
                mHero->SetState(HeroState::BigJump);
                break;
            } else {
                // 小ジャンプ
                mHero->SetState(HeroState::SmallJump);
                break;
            }
        }
    } break;

    case HeroState::AirIdle: {
        if (com.moveAxis.Length() > mStickDeadZone) {
            mHero->SetState(HeroState::AirMove);
            break;
        }
        if (com.jump && !preCom.jump) {
            if (mHero->mCurrentStatus.airJumpCount == 0) {
                mHero->SetState(HeroState::AirPreJump);
            }
            break;
        }
    } break;
    case HeroState::AirMove: {
        if (com.moveAxis.Length() > mStickDeadZone) {
            Vector2& velocity = mHero->mCurrentStatus.velocity;
            float maxAirSpeed = mHero->GetBaseStatus().maxAirSpeed;

            Vector2 accelerationDir = mMoveAxisNorm * maxAirSpeed - velocity;
            if (accelerationDir.Length() > 0) {
                velocity += Vector2::Normalize(accelerationDir) * mHero->GetBaseStatus().airAcceleration;
            }
            if (velocity.Length() > maxAirSpeed) {
                velocity = Vector2::Normalize(velocity) * maxAirSpeed;
            }

            if (com.jump && !preCom.jump) {
                if (mHero->mCurrentStatus.airJumpCount == 0) {
                    mHero->SetState(HeroState::AirPreJump);
                }
                break;
            }
        } else {
            mHero->SetState(HeroState::AirIdle);
        }
    } break;
    case HeroState::KnockBack: {
    } break;
    case HeroState::Death: {
    } break;
    default:
        break;
    }
    // std::cout << "air j cout" << mHero->mCurrentStatus.airJumpCount << std::endl;
    // std::cout << "run command6" << std::endl;
}
void PlayerMove::DefeatedUpdate()
{
    CommandData com    = mPlayer->GetCommandData();
    CommandData preCom = mPlayer->GetPreCommandData();
    if (com.attack1 && !preCom.attack1) {
        DefeatedAction1();
        // std::cout << "defeat1" << std::endl;
    }
    if (com.attack2 && !preCom.attack2) {
        DefeatedAction2();
        // std::cout << "defeat2" << std::endl;
    }
    if (com.jump && !preCom.jump) {
        DefeatedAction3();
        // std::cout << "defeat3" << std::endl;
    }
}

void PlayerMove::DefeatedAction3()
{
    std::srand(std::time(nullptr));
    int random = std::rand();
    if (random % 20) {
        DefeatedAction3Normal();
    } else {
        DefeatedAction3Special();
    }
}