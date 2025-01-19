#include "heroBodyMove.h"
#include "../../../../../common/src/component/transform.h"
#include "../../../../../utils/src/math.h"
#include "../../gameObject/HeroBody.h"
#include "../../gameObject/effect/knockbackSmokeEffect.h"
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
    if (mHero->mCurrentStatus.stopFrame > 0) {
        return;
    }
    switch (mHero->mCurrentStatus.state) {
    case HeroState::Idle: {
        Vector2 faceDir = mHero->mCurrentStatus.faceDir;
        float angle     = Math::Atan2(faceDir.x, -faceDir.y);
        Quaternion q    = Quaternion(Vector3(0.0f, 1.0f, 0.0f), -angle);
        Quaternion resultQ;
        float slerpTime = 20.0f;
        if (mHero->mCurrentStatus.actionFrame < slerpTime) {
            Quaternion preQ = GetTransform()->GetLocalRotation();
            resultQ         = Quaternion::Slerp(preQ, q, (mHero->mCurrentStatus.actionFrame + 1.0f) / slerpTime);
        } else {
            resultQ = q;
        }
        GetTransform()->SetWorldRotation(resultQ);
    } break;
    case HeroState::Walking: {
        Vector2 faceDir = mHero->mCurrentStatus.faceDir;
        float angle     = Math::Atan2(faceDir.x, -faceDir.y);
        Quaternion q    = Quaternion(Vector3(0.0f, 1.0f, 0.0f), -angle);
        Quaternion resultQ;
        float slerpTime = 20.0f;
        if (mHero->mCurrentStatus.actionFrame < slerpTime) {
            Quaternion preQ = GetTransform()->GetLocalRotation();
            resultQ         = Quaternion::Slerp(preQ, q, (mHero->mCurrentStatus.actionFrame + 1.0f) / slerpTime);
        } else {
            resultQ = q;
        }
        GetTransform()->SetWorldRotation(resultQ);
    } break;
    case HeroState::Running: {
        Vector2 faceDir = mHero->mCurrentStatus.faceDir;
        float angle     = Math::Atan2(faceDir.x, -faceDir.y);
        Quaternion q    = Quaternion(Vector3(0.0f, 1.0f, 0.0f), -angle);
        Quaternion resultQ;
        float slerpTime = 20.0f;
        if (mHero->mCurrentStatus.actionFrame < slerpTime) {
            Quaternion preQ = GetTransform()->GetLocalRotation();
            resultQ         = Quaternion::Slerp(preQ, q, (mHero->mCurrentStatus.actionFrame + 1.0f) / slerpTime);
        } else {
            resultQ = q;
        }
        GetTransform()->SetWorldRotation(resultQ);
    } break;
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
        Vector2 faceDir = mHero->mCurrentStatus.faceDir;
        float angle     = Math::Atan2(faceDir.x, -faceDir.y);
        Quaternion q    = Quaternion(Vector3(0.0f, 1.0f, 0.0f), -angle);
        Quaternion resultQ;
        float slerpTime = 20.0f;
        if (mHero->mCurrentStatus.actionFrame < slerpTime) {
            Quaternion preQ = GetTransform()->GetLocalRotation();
            resultQ         = Quaternion::Slerp(preQ, q, (mHero->mCurrentStatus.actionFrame + 1.0f) / slerpTime);
        } else {
            resultQ = q;
        }
        GetTransform()->SetWorldRotation(resultQ);
    } break;
    case HeroState::AirMove: {
        Vector2 faceDir = mHero->mCurrentStatus.faceDir;
        float angle     = Math::Atan2(faceDir.x, -faceDir.y);
        Quaternion q    = Quaternion(Vector3(0.0f, 1.0f, 0.0f), -angle);
        Quaternion resultQ;
        float slerpTime = 20.0f;
        if (mHero->mCurrentStatus.actionFrame < slerpTime) {
            Quaternion preQ = GetTransform()->GetLocalRotation();
            resultQ         = Quaternion::Slerp(preQ, q, (mHero->mCurrentStatus.actionFrame + 1.0f) / slerpTime);
        } else {
            resultQ = q;
        }
        GetTransform()->SetWorldRotation(resultQ);
    } break;
    case HeroState::KnockBack: {
        if (!mHero->mCurrentStatus.onGround) {
            Quaternion rotation = Quaternion::Concatenate(Quaternion(Vector3(1.0f, 0.0f, 0.0f), Math::ToRadians(10.0f)), GetTransform()->GetLocalRotation());
            GetTransform()->SetLocalRotation(rotation);
        }
        if (mHero->mCurrentStatus.knockbackTime > 6) {
            if (mHero->mCurrentStatus.knockbackTime % 3 == 0) {
                new KnockbackSmokeEffect(GetTransform()->GetWorldPosition());
                // std::cout << "mHero->mCurrentStatus.knockbackTime % 3 == 0" << std::endl;
            }
        }
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
