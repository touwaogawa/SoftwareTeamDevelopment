#include "beyMove.h"
#include "../../../../../utils/src/math.h"
#include "../../../component/transform.h"
#include "../../gameObject/bey.h"
#include "../../gameObject/hero.h"
#include <iostream>

BeyMove::BeyMove(Bey* owner)
    : Behaviour(owner)
    , mBey(owner)
    , mHero(nullptr)
    , mSpinPower(0.0f)
    , mMinSpinPower(0.0f)
    , mRotationSpeed(0.0f)
{
    // std::cout << "beyMove constructor" << std::endl;
}

void BeyMove::Start()
{
    mHero = mBey->GetHero();
    // std::cout << "beyMove start" << std::endl;
    mSpinPower    = 6.0f;
    mMinSpinPower = 6.0f;

    // if (mTransform->GetParent()) {
    //     std::cout << "Bey has pa from Beymove mTransform" << std::endl;
    // }
    // if (mOwner->GetTransform()->GetParent()) {
    //     std::cout << "Bey has pa ffrom Beymove mOwner Gettrans" << std::endl;
    // }
}
namespace {

}
void BeyMove::Update()
{
    mRotationSpeed += mSpinPower;
    switch (mHero->mCurrentStatus.state) {
    case HeroState::Idle:
    case HeroState::Walking:
    case HeroState::Running:
        break;
    case HeroState::RunningAttack: {
        mRotationSpeed += 4.0f;
    } break;
    case HeroState::PreJump: {
    } break;
    case HeroState::AirIdle: {
    } break;
    case HeroState::KnockBack: {
        mRotationSpeed -= 1.0f;
    } break;
    case HeroState::HitStop: {
    } break;
    case HeroState::Death: {
    } break;
    default:
        // std::cout << "HeroState error" << std::endl;
        break;
    }
    if (mHero->mCurrentStatus.stopFrame <= 0) {
        GetTransform()->SetLocalRotation(
            Quaternion(Vector3(0.0f, -1.0f, 0.0f), Math::ToRadians(mRotationSpeed)));
    }
}
void BeyMove::LateUpdate()
{
}
