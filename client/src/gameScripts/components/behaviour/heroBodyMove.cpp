#include "heroBodyMove.h"
#include "../../../../../common/src/component/transform.h"
#include "../../../../../utils/src/math.h"
#include "../../gameObject/HeroBody.h"
#include "../../gameObject/hero.h"
#include <iostream>

HeroBodyMove::HeroBodyMove(HeroBody* owner, Hero* hero)
    : Behaviour(owner)
    , mHeroBody(owner)
    , mHero(hero)
{
    // std::cout << "HeroBodyMove constructor" << std::endl;
}

void HeroBodyMove::Start()
{
}

void HeroBodyMove::Update()
{
    switch (mHero->mCurrentStatus.state) {
    case HeroState::Idle:
        break;
    case HeroState::Walking:
        break;
    case HeroState::Running:
        break;
    case HeroState::PreRunningAttack: {
    } break;
    case HeroState::RunningAttack: {
    } break;
    case HeroState::AfterRunningAttack: {
    } break;
    case HeroState::PreFallAttack: {

    } break;
    case HeroState::FallAttack: {

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
    } break;
    case HeroState::Death: {
    } break;
    default:
        // std::cout << "HeroState error" << std::endl;
        break;
    }
}
void HeroBodyMove::LateUpdate()
{
}
