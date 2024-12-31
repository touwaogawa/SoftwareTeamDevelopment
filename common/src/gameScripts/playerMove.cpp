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
    mBattleScene                = static_cast<BattleScene*>(mOwner->GetScene());
    mPlayer                     = static_cast<Player*>(mOwner);
    mHero                       = mPlayer->GetHero();
    mHeroMove                   = static_cast<HeroMove*>(mHero->GetBehaviour());
    mGravity                    = mBattleScene->GetStage()->GetGravity();
    mHero->mCurrentStatus.state = HeroState::Idle;
    double radius               = 13.0;
    double angle                = Math::TwoPi * mPlayer->GetID() / mBattleScene->GetPlayerNum(); // 等間隔の角度（ラジアン）
    double x                    = radius * cos(angle);
    double y                    = radius * sin(angle);
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
            switch (mHero->mCurrentStatus.state) {
            case HeroState::Idle:
                // std::cout << "idle" << std::endl;
                if (commandData.moveAxis.Length() > stickDeadZone) {
                    // 移動スティック倒していた場合
                    if (commandData.moveAxis.Length() - mPlayer->prevCommandData.moveAxis.Length() < 0.3) {
                        mHero->mCurrentStatus.state = HeroState::Walking;
                    } else {
                        mHero->mCurrentStatus.state = HeroState::StartRunning;
                        mHero->mCurrentStatus.speed = mHero->GetInitialDushSpeed();
                    }
                } else {
                    if (mHero->mCurrentStatus.speed != 0.0f) {
                        mHero->mCurrentStatus.speed = 0.0f;
                    }
                }
                break;
            case HeroState::Walking:
                // std::cout << "walk" << std::endl;
                if (commandData.moveAxis.Length() < stickDeadZone) {
                    mHero->mCurrentStatus.state = HeroState::Idle;
                } else {
                    mHeroMove->Walking(commandData.moveAxis);
                }
                break;
            case HeroState::StartRunning:
                // std::cout << "Startrun" << std::endl;
                if (commandData.moveAxis.Length() < stickDeadZone) {
                    mHero->mCurrentStatus.state = HeroState::StopRunning;
                } else {
                    mHeroMove->StartRunning(commandData.moveAxis);
                    if (mHero->mCurrentStatus.speed >= mHero->GetMaxRunSpeed()) {
                        mHero->mCurrentStatus.state = HeroState::Running;
                    }
                }
                break;
            case HeroState::Running:
                // std::cout << "run" << std::endl;
                if (commandData.attack1 && !mPlayer->prevCommandData.attack1) {
                    mHeroMove->StartRunningAttack(commandData.moveAxis);
                    mHero->mCurrentStatus.state = HeroState::RunningAttack;
                    break;
                }
                if (commandData.moveAxis.Length() < stickDeadZone) {
                    mHero->mCurrentStatus.state = HeroState::StopRunning;
                } else {
                    mHeroMove->Running(commandData.moveAxis);
                }
                break;
            case HeroState::StopRunning:
                // std::cout << "stoprun" << std::endl;
                if (commandData.moveAxis.Length() >= stickDeadZone) {
                    mHero->mCurrentStatus.state = HeroState::StartRunning;
                } else {
                    mHeroMove->StopRunning(commandData.moveAxis);
                    if (0.0f == mHero->mCurrentStatus.speed) {
                        mHero->mCurrentStatus.state = HeroState::Idle;
                    }
                }
                break;
            case HeroState::RunningAttack:
                // std::cout << "runAtk" << std::endl;
                if (!mHeroMove->UpdateRunningAttack())
                    mHero->mCurrentStatus.state = HeroState::Idle;

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