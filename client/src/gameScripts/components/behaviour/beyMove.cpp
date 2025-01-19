#include "beyMove.h"
#include "../../../../../common/src/component/transform.h"
#include "../../../../../utils/src/math.h"
#include "../../gameObject/bey.h"
#include "../../gameObject/hero.h"
#include <iostream>

BeyMove::BeyMove(Bey* owner, Hero* hero)
    : Behaviour(owner)
    , mBey(owner)
    , mHero(hero)
    , mSpinPower(0.0f)
    , mMinSpinPower(0.0f)
{
    // std::cout << "beyMove constructor" << std::endl;
}

void BeyMove::Start()
{
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
    switch (mHero->mCurrentStatus.state) {
    case HeroState::Idle:
        mSpinPower = 6.0f;
        break;
    case HeroState::Walking:
        mSpinPower = 6.0f;
        break;
    case HeroState::Running:
        mSpinPower = 6.0f;
        break;
    case HeroState::PreRunningAttack: {
        mSpinPower += 3.0f;
    } break;
    case HeroState::RunningAttack: {
    } break;
    case HeroState::AfterRunningAttack: {
        mSpinPower -= 1.0f;
    } break;
    case HeroState::PreFallAttack: {

    } break;
    case HeroState::FallAttack: {
        mSpinPower = 0.0f;

    } break;
    case HeroState::AfterFallAttack: {

    } break;
    case HeroState::PreAirFrontAttack: {

    } break;
    case HeroState::AirFrontAttack: {

    } break;
    case HeroState::AfterAirFrontAttack: {

    } break;
    case HeroState::PreAirBackAttack: {

    } break;
    case HeroState::AirBackAttack: {

    } break;
    case HeroState::AfterAirBackAttack: {

    } break;
    case HeroState::PreJump: {
    } break;
    case HeroState::AirIdle: {
    } break;
    case HeroState::KnockBack: {
        mSpinPower = 10.0f;
    } break;
    case HeroState::Death: {
    } break;
    default:
        // std::cout << "HeroState error" << std::endl;
        break;
    }
    if (mHero->mCurrentStatus.stopFrame <= 0) {
        Quaternion rotation = Quaternion::Concatenate(GetTransform()->GetLocalRotation(), Quaternion(Vector3(0.0f, -1.0f, 0.0f), Math::ToRadians(mSpinPower)));
        GetTransform()->SetLocalRotation(rotation);
    }
}
void BeyMove::LateUpdate()
{
}
