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
    case HeroState::Running:
    case HeroState::RunningAttack: {
        if (mHero->mCurrentStatus.stopFrame <= 0) {
            Vector2 faceDir = mHero->mCurrentStatus.faceDir;
            if (faceDir.Length() > 0.0f) {
                float angle  = Math::Atan2(faceDir.x, -faceDir.y);
                Quaternion q = Quaternion(Vector3(0.0f, 1.0f, 0.0f), -angle);
                GetTransform()->SetWorldRotation(q);
            }
        }
    } break;
    case HeroState::PreJump: {
    } break;
    case HeroState::AirIdle: {
    } break;
    case HeroState::KnockBack: {
        if (mHero->mCurrentStatus.stopFrame <= 0) {
            Quaternion rotation = Quaternion::Concatenate(GetTransform()->GetWorldRotation(), Quaternion(Vector3(0.0f, -1.0f, 0.0f), Math::ToRadians(10.0f)));
            GetTransform()->SetLocalRotation(rotation);
        }
    } break;
    case HeroState::Death: {
    } break;
    default:
        // std::cout << "HeroState error" << std::endl;
        break;
    }
}
void RiderMove::LateUpdate()
{
}
