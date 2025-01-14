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
    , dir_x(0.0f)
    , dir_y(0.0f)
{
    // std::cout << "riderMove constructor" << std::endl;
}

void RiderMove::Start()
{
    // std::cout << "riderMove start" << std::endl;
    mHero = mRider->GetHero();
    dir_x = 0.0f;
    dir_y = 0.0f;

    // if (mTransform->GetParent()) {
    //     std::cout << "rider has pa from ridermove mTransform" << std::endl;
    // }
    // if (mOwner->GetTransform()->GetParent()) {
    //     std::cout << "rider has pa ffrom ridermove mOwner Gettrans" << std::endl;
    // }
}

void RiderMove::Update()
{
    // std::cout << "rider pos x: " << mTransform->GetWorldPosition().x << std::endl;
    // std::cout << "rider pos y: " << mTransform->GetWorldPosition().y << std::endl;
    // std::cout << "rider pos z: " << mTransform->GetWorldPosition().z << std::endl;

    // std::cout << "ow rider pos x: " << mOwner->GetTransform()->GetWorldPosition().x << std::endl;
    // std::cout << "ow rider pos y: " << mOwner->GetTransform()->GetWorldPosition().y << std::endl;
    // std::cout << "ow rider pos z: " << mOwner->GetTransform()->GetWorldPosition().z << std::endl;

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
                // Vector3 eulerAngles(0.0f, angle, 0.0f); // XとZは0で、Yだけ設定
                Quaternion q = Quaternion(Vector3(0.0f, 1.0f, 0.0f), angle);
                mTransform->SetWorldRotation(q);
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
