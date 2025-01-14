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
{
    // std::cout << "beyMove constructor" << std::endl;
}

void BeyMove::Start()
{
    mHero = mBey->GetHero();
    // std::cout << "beyMove start" << std::endl;
    mSpinPower    = 0.1;
    mMinSpinPower = 0.1;

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

    if (mHero->mStopFrame <= 0) {
        Matrix4 mat = Matrix4::CreateRotationY(Math::ToRadians(24));
        mTransform->TransformationLocalMatrix(mat);
    }
    switch (mHero->mCurrentStatus.state) {
    case HeroState::Idle:
    case HeroState::Walking:
    case HeroState::StartRunning:
    case HeroState::Running:
    case HeroState::StopRunning:
    case HeroState::RunningAttack: {
        // mTransform->SetWorldEulerAngles(Vector3())
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
void BeyMove::LateUpdate()
{
}
