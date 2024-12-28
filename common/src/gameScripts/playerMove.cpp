#include "playerMove.h"
#include "../../../client/src/beySmashEngine.h"
#include "../../../client/src/scenes/battle.h"
#include "hero/heroMove.h"
#include "player.h"
#include "stage/stage.h"

PlayerMove::PlayerMove(GameObject* owner)
    : Behaviour(owner)
{
}

void PlayerMove::Start()
{
    mBattleScene         = static_cast<BattleScene*>(mOwner->GetScene());
    mPlayer              = static_cast<Player*>(mOwner);
    mHero                = static_cast<Hero*>(mPlayer->GetHero());
    mHeroMove            = static_cast<HeroMove*>(mHero->GetBehaviour());
    mGravity             = mBattleScene->GetStage()->GetGravity();
    mHero->currentStatus = HeroStatus::Idle;
    double radius        = 13.0;
    double angle         = Math::TwoPi * mPlayer->GetID() / mBattleScene->GetPlayerNum(); // 等間隔の角度（ラジアン）
    double x             = radius * cos(angle);
    double y             = radius * sin(angle);
    mHero->GetTransform()->SetWorldPosition(x, 0.0f, y);
}
namespace {

}
void PlayerMove::Update()
{
    if (!mPlayer->commandBuffer.empty()) {
        CommandData commandData = mPlayer->commandBuffer.back();
        int commandDelay        = 1;
        if (commandData.frame <= mBattleScene->currentFrame - commandDelay) {
            // commandDelayフレームより過去のコマンドを実行
            // CommandDataCout(commandData);
            float stickDeadZone = 0.1;
            switch (mHero->currentStatus) {
            case HeroStatus::Idle:
                // std::cout << "idle" << std::endl;
                if (commandData.moveAxis.Length() > stickDeadZone) {
                    // 移動スティック倒していた場合
                    if (commandData.moveAxis.Length() - mPlayer->prevCommandData.moveAxis.Length() < 0.3) {
                        mHero->currentStatus = HeroStatus::Walking;
                    } else {
                        mHero->currentStatus = HeroStatus::StartRunning;
                        mHero->currentSpeed  = mHero->GetInitialDushSpeed();
                    }
                } else {
                    if (mHero->currentSpeed != 0.0f) {
                        mHero->currentSpeed = 0.0f;
                    }
                }
                break;
            case HeroStatus::Walking:
                // std::cout << "walk" << std::endl;
                if (commandData.moveAxis.Length() < stickDeadZone) {
                    mHero->currentStatus = HeroStatus::Idle;
                } else {
                    mHeroMove->Walking(commandData.moveAxis);
                }
                break;
            case HeroStatus::StartRunning:
                // std::cout << "Startrun" << std::endl;
                if (commandData.moveAxis.Length() < stickDeadZone) {
                    mHero->currentStatus = HeroStatus::StopRunning;
                } else {
                    mHeroMove->StartRunning(commandData.moveAxis);
                    if (mHero->currentSpeed >= mHero->GetMaxRunSpeed()) {
                        mHero->currentStatus = HeroStatus::Running;
                    }
                }
                break;
            case HeroStatus::Running:
                // std::cout << "run" << std::endl;
                if (commandData.attack1 && !mPlayer->prevCommandData.attack1) {
                    mHeroMove->StartRunningAttack(commandData.moveAxis);
                    mHero->currentStatus = HeroStatus::RunningAttack;
                    break;
                }
                if (commandData.moveAxis.Length() < stickDeadZone) {
                    mHero->currentStatus = HeroStatus::StopRunning;
                } else {
                    mHeroMove->Running(commandData.moveAxis);
                }
                break;
            case HeroStatus::StopRunning:
                // std::cout << "stoprun" << std::endl;
                if (commandData.moveAxis.Length() >= stickDeadZone) {
                    mHero->currentStatus = HeroStatus::StartRunning;
                } else {
                    mHeroMove->StopRunning(commandData.moveAxis);
                    if (0.0f == mHero->currentSpeed) {
                        mHero->currentStatus = HeroStatus::Idle;
                    }
                }
                break;
            case HeroStatus::RunningAttack:
                // std::cout << "runAtk" << std::endl;
                if (!mHeroMove->UpdateRunningAttack())
                    mHero->currentStatus = HeroStatus::Idle;

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