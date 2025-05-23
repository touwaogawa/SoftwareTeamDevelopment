#include "riderMove.h"
#include "../../../../../common/src/component/transform.h"
#include "../../../../../utils/src/math.h"
#include "../../gameObject/hero.h"
#include "../../gameObject/rider.h"
#include <iostream>

RiderMove::RiderMove(Rider* owner, Hero* hero)
    : Behaviour(owner)
    , mRider(owner)
    , mHero(hero)
    , dir_x(0.0f)
    , dir_y(0.0f)
{
    // std::cout << "riderMove constructor" << std::endl;
}

void RiderMove::Start()
{
    // std::cout << "riderMove start" << std::endl;
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
    } break;
    case HeroState::PreJump: {
    } break;
    case HeroState::AirIdle: {
    } break;
    case HeroState::KnockBack: {
        if (mHero->mCurrentStatus.stopFrame <= 0) {
            Quaternion rotation = Quaternion::Concatenate(GetTransform()->GetLocalRotation(), Quaternion(Vector3(0.0f, -1.0f, 0.0f), Math::ToRadians(10.0f)));
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
