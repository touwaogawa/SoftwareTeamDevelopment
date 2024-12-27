#include "playerMove.h"
#include "../beySmashEngine.h"
#include "../scenes/battle.h"
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
            float stickDeadZone = 0.2;
            switch (mHero->currentStatus) {
            case HeroStatus::Idle:
                std::cout << "idle" << std::endl;
                if (commandData.moveAxis.Length() > stickDeadZone) {
                    // 移動スティック倒していた場合
                    if (commandData.moveAxis.Length() - mPlayer->prevCommandData.moveAxis.Length() < 0.4) {
                        mHero->currentStatus = HeroStatus::Walking;
                    } else {
                        mHero->currentStatus = HeroStatus::Running;
                    }
                } else if (0.0f < mHero->currentSpeed) {
                    // 減速処理
                    if (mHero->currentSpeed < 0.05f) {
                        mHero->currentSpeed = 0.0f;
                    } else {
                        mHero->currentSpeed -= mHero->GetTraction() * mGravity;
                        if (mHero->currentSpeed < 0.0f) {
                            mHero->currentSpeed = 0.0f;
                        }
                    }
                }
                break;
            case HeroStatus::Walking:
                std::cout << "walk" << std::endl;
                if (commandData.moveAxis.Length() < stickDeadZone) {
                    // スティックデッドゾーン
                    mHero->currentStatus = HeroStatus::Idle;
                } else {
                    mHero->currentMoveAxis = commandData.moveAxis;
                    if (mHero->currentSpeed < mHero->GetMaxWalkSpeed()) {
                        mHero->currentSpeed = std::min(mHero->GetMaxWalkSpeed(), mHero->currentSpeed + mHero->GetWalkAcceleration());
                    }
                }
                break;
            case HeroStatus::Running:
                std::cout << "run" << std::endl;
                if (commandData.moveAxis.Length() < stickDeadZone) {
                    // スティックデッドゾーン
                    mHero->currentStatus = HeroStatus::Idle;
                } else {
                    mHero->currentMoveAxis = commandData.moveAxis;
                    if (mHero->currentSpeed < mHero->GetMaxWalkSpeed()) {
                        mHero->currentSpeed = std::min(mHero->GetMaxRunSpeed(), mHero->currentSpeed + mHero->GetDushAcceleration());
                    }
                }
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