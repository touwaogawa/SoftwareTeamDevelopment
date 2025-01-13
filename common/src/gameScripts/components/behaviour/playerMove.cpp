#include "playerMove.h"
#include "../../../component/transform.h"
#include "../../../scene.h"
#include "../../gameObject/hero.h"
#include "../../gameObject/player.h"
#include "../../gameObject/stage.h"
#include "heroMove.h"
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
            case HeroState::RunningAttack:
                // std::cout << "runAtk" << std::endl;

                break;
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
void PlayerMove::LateUpdate()
{
}

// ##############################################