#include "riderMove.h"
#include "../../../../../utils/src/math.h"
#include "../../../component/transform.h"
#include "../../gameObject/hero.h"
#include "../../gameObject/rider.h"
#include <iostream>

RiderMove::RiderMove(Rider* owner)
    : Behaviour(owner)
    , mRider(owner)
    , mHero(nullptr)
{
    // std::cout << "riderMove constructor" << std::endl;
}

void RiderMove::Start()
{
    // std::cout << "riderMove start" << std::endl;
    mHero = mRider->GetHero();
    dir_x = 0.0f;
    dir_y = 0.0f;
}

void RiderMove::Update()
{
    switch (mHero->mCurrentStatus.state) {
    case HeroState::Idle:
    case HeroState::Walking:
    case HeroState::StartRunning:
    case HeroState::Running:
    case HeroState::StopRunning:
    case HeroState::RunningAttack: {
        if (mHero->mStopFrame <= 0) {
            Vector2 faceDir = mHero->mCurrentStatus.faceDir;

            // ベクトルの長さがゼロでないことを確認
            if (faceDir.Length() > 0.0f) {
                // Y軸回転角度を計算
                float angle = Math::Atan2(faceDir.y, faceDir.x) - Math::PiOver2;

                // オイラー角を直接設定
                Vector3 eulerAngles(0.0f, angle, 0.0f); // XとZは0で、Yだけ設定
                mTransform->SetWorldEulerAngles(eulerAngles);
            }
        }
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
void RiderMove::LateUpdate()
{
}
