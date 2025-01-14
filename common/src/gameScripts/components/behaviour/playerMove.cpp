#include "playerMove.h"
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
        // std::cout << "defeat" << std::endl;
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
    // if (!mPlayer->commandBuffer.empty()) {
    //     CommandData commandData = mPlayer->commandBuffer.back();
    //     int commandDelay        = 1;
    //     if (commandData.frame <= mPlayer->GetScene()->currentFrame - commandDelay) {
    //     }
    // }
}
void PlayerMove::BattleUpdate()
{
    if (!mPlayer->commandBuffer.empty()) {
        CommandData commandData     = mPlayer->commandBuffer.back();
        CommandData prevCommandData = mPlayer->prevCommandData;
        int commandDelay            = 1;
        if (commandData.frame <= mPlayer->GetScene()->currentFrame - commandDelay) {
            // commandDelayフレームより過去のコマンドを実行
            // CommandDataCout(commandData);
            float stickDeadZone           = 0.1;
            mHero->mCurrentStatus.moveDir = Vector2::Normalize(commandData.moveAxis);
            switch (mHero->mCurrentStatus.state) {
            case HeroState::Idle:
                // std::cout << "idle" << std::endl;
                mHero->mCurrentStatus.faceDir = Vector2::Normalize(commandData.moveAxis);
                if (commandData.moveAxis.Length() > stickDeadZone) {
                    // 移動スティック倒していた場合
                    if (commandData.moveAxis.Length() - prevCommandData.moveAxis.Length() < 0.3) {
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
                mHero->mCurrentStatus.faceDir = Vector2::Normalize(commandData.moveAxis);
                if (commandData.moveAxis.Length() < stickDeadZone) {
                    mHero->mCurrentStatus.state = HeroState::Idle;
                } else if (commandData.attack1 && !prevCommandData.attack1) {
                    mHero->mCurrentStatus.state = HeroState::RunningAttack;
                    break;
                }
                break;
            case HeroState::StartRunning:
                // std::cout << "Startrun" << std::endl;
                mHero->mCurrentStatus.faceDir = Vector2::Normalize(commandData.moveAxis);
                if (commandData.moveAxis.Length() < stickDeadZone) {
                    mHero->mCurrentStatus.state = HeroState::StopRunning;
                } else if (commandData.attack1 && !prevCommandData.attack1) {
                    mHero->mCurrentStatus.state = HeroState::RunningAttack;
                    break;
                }
                break;
            case HeroState::Running:
                mHero->mCurrentStatus.faceDir = Vector2::Normalize(commandData.moveAxis);
                // std::cout << "run" << std::endl;
                if (commandData.moveAxis.Length() < stickDeadZone) {
                    mHero->mCurrentStatus.state = HeroState::StopRunning;
                } else if (commandData.attack1 && !prevCommandData.attack1) {
                    mHero->mCurrentStatus.state = HeroState::RunningAttack;
                    break;
                }
                if (commandData.jump && !prevCommandData.jump) {
                    // mHero->mCurrentStatus.state = HeroState::PreJump;
                    break;
                }
                break;
            case HeroState::StopRunning:
                // std::cout << "stoprun" << std::endl;
                mHero->mCurrentStatus.faceDir = Vector2::Normalize(commandData.moveAxis);
                if (commandData.moveAxis.Length() >= stickDeadZone) {
                    mHero->mCurrentStatus.state = HeroState::StartRunning;
                }
                break;
            case HeroState::RunningAttack: {
            } break;
            case HeroState::PreJump: {
                mHero->mCurrentStatus.faceDir = Vector2::Normalize(commandData.moveAxis);
                if (mHero->mActionFrame >= 3) {
                    if (commandData.jump) {
                        // 大ジャンプ
                        // mHero->SetState(HeroState::BigJump);
                        break;
                    } else {
                        // 小ジャンプ
                        // mHero->SetState(HeroState::SmallJump);
                        break;
                    }
                }
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
        // std::cout << "def empty" << std::endl;
        CommandData commandData     = mPlayer->commandBuffer.back();
        CommandData prevCommandData = mPlayer->prevCommandData;
        int commandDelay            = 1;
        if (commandData.frame <= mPlayer->GetScene()->currentFrame - commandDelay) {
            if (commandData.attack1 && !prevCommandData.attack1) {
                DefeatedAction1();
                // std::cout << "defeat1" << std::endl;
            }
            if (commandData.attack2 && !prevCommandData.attack2) {
                DefeatedAction2();
                // std::cout << "defeat2" << std::endl;
            }
            if (commandData.jump && !prevCommandData.jump) {
                DefeatedAction3();
                // std::cout << "defeat3" << std::endl;
            }
            mPlayer->commandBuffer.pop_back();
        }
        mPlayer->prevCommandData = commandData;
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