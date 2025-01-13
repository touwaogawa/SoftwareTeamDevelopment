#include "playerMove.h"
#include "../../../component/rigidBody.h"
#include "../../../component/transform.h"
#include "../../../scene.h"
#include "../../gameObject/hero.h"
#include "../../gameObject/player.h"
#include "../../gameObject/stage.h"
#include "heroMove.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

PlayerMove::PlayerMove(Player* owner)
    : Behaviour(owner)
    , mPlayer(owner)
{
}

void PlayerMove::Start()
{
    // std::cout << "playerMove start" << std::endl;
    mHero                       = mPlayer->GetHero();
    mHero->mCurrentStatus.state = HeroState::Idle;

    RigidBody* r = mHero->GetComponent<RigidBody>();
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

}
void PlayerMove::Update()
{
    switch (mPlayer->GetPlayerState()) {
    case PlayerState::Init:
        InitUpdate();
        break;
    case PlayerState::Battle:
        BattleUpdate();
        break;
    case PlayerState::Defeat:
        DefeatedUpdate();
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
    if (!mPlayer->commandBuffer.empty()) {
        CommandData commandData = mPlayer->commandBuffer.back();
        int commandDelay        = 1;
        if (commandData.frame <= mPlayer->GetScene()->currentFrame - commandDelay) {
        }
    }
}
void PlayerMove::BattleUpdate()
{
    if (!mPlayer->commandBuffer.empty()) {
        CommandData commandData = mPlayer->commandBuffer.back();
        int commandDelay        = 1;
        if (commandData.frame <= mPlayer->GetScene()->currentFrame - commandDelay) {
            // commandDelayフレームより過去のコマンドを実行
            // CommandDataCout(commandData);
            float stickDeadZone           = 0.1;
            mHero->mCurrentStatus.moveDir = Vector2::Normalize(commandData.moveAxis);
            switch (mHero->mCurrentStatus.state) {
            case HeroState::Idle:
                // std::cout << "idle" << std::endl;
                if (commandData.moveAxis.Length() > stickDeadZone) {
                    // 移動スティック倒していた場合
                    if (commandData.moveAxis.Length() - mPlayer->prevCommandData.moveAxis.Length() < 0.3) {
                        // 弱く倒す
                        mHero->mCurrentStatus.state = HeroState::Walking;
                    } else {
                        // 強く倒す
                        mHero->mCurrentStatus.state = HeroState::StartRunning;
                    }
                }
                break;
            case HeroState::Walking:
                // std::cout << "walk" << std::endl;
                if (commandData.moveAxis.Length() < stickDeadZone) {
                    mHero->mCurrentStatus.state = HeroState::Idle;
                }
                break;
            case HeroState::StartRunning:
                // std::cout << "Startrun" << std::endl;
                if (commandData.moveAxis.Length() < stickDeadZone) {
                    mHero->mCurrentStatus.state = HeroState::StopRunning;
                }
                break;
            case HeroState::Running:
                // std::cout << "run" << std::endl;
                // if (commandData.attack1 && !mPlayer->prevCommandData.attack1) {
                //     mHero->mCurrentStatus.state = HeroState::RunningAttack;
                //     break;
                // }
                if (commandData.jump) {
                    mHero->mCurrentStatus.state = HeroState::PreJump;
                    break;
                }
                if (commandData.moveAxis.Length() < stickDeadZone) {
                    mHero->mCurrentStatus.state = HeroState::StopRunning;
                }
                break;
            case HeroState::StopRunning:
                // std::cout << "stoprun" << std::endl;
                if (commandData.moveAxis.Length() >= stickDeadZone) {
                    mHero->mCurrentStatus.state = HeroState::StartRunning;
                }
                break;
            case HeroState::RunningAttack: {
            } break;
            case HeroState::PreJump: {
                if (mHero->mActionFrame >= 3) {
                    rp3d::Vector3 vel = mHeroRp3dRigidBody->getLinearVelocity();
                    if (commandData.jump) {
                        // 大ジャンプ
                        mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(vel.x, 20.0, vel.z));
                    } else {
                        // 小ジャンプ
                        mHeroRp3dRigidBody->setLinearVelocity(rp3d::Vector3(vel.x, 8.0, vel.z));
                    }
                    mHero->mCurrentStatus.state = HeroState::AirIdle;
                }
            } break;
            case HeroState::AirIdle: {
            } break;
            case HeroState::Death: {
            } break;
            default:
                break;
            }
            // コマンドバッファからコマンド削除
            mPlayer->commandBuffer.pop_back();
        }
        mPlayer->prevCommandData = commandData;
    } else {
        // コマンドバッファが空のとき
    }
}
void PlayerMove::DefeatedUpdate()
{
    if (!mPlayer->commandBuffer.empty()) {
        CommandData commandData = mPlayer->commandBuffer.back();
        int commandDelay        = 1;
        if (commandData.frame <= mPlayer->GetScene()->currentFrame - commandDelay) {
            if (commandData.attack1) {
                DefeatedAction1();
            }
            if (commandData.attack2) {
                DefeatedAction2();
            }
            if (commandData.jump) {
                DefeatedAction3();
            }
        }
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