#include "pressAnyButtonMove.h"
#include "../../../../../common/src/component/transform.h"
#include "../../../../../common/src/gameObject.h"
#include "../../../../../utils/src/input.h"
#include "../../../audio.h"
#include "../../../component/camera.h"
#include <iostream>

PressAnyButtonMove::PressAnyButtonMove(GameObject* owner)
    : Behaviour(owner)
    , mStatus(PressAnyButtonMoveStatus::Init)
    , mTheta(0.0f)
    , mMoveRange(0.0f)
    , mBasePosX(0.0f)
    , mBasePosY(0.0f)
    , mBasePosZ(0.0f)
    , mActionFrame(0)
{
}

void PressAnyButtonMove::Start()
{
    mTheta            = 0.0f;
    mMoveRange        = 20.0f;
    mBasePosX         = mOwner->GetTransform()->GetWorldPosition().x;
    mBasePosY         = mOwner->GetTransform()->GetWorldPosition().y;
    mBasePosZ         = mOwner->GetTransform()->GetWorldPosition().z;
    mChunk_GoMatching = Audio::GetMixChunk("../assets/sounds/se/決定ボタンを押す18.mp3");
}
void PressAnyButtonMove::Update()
{
    float offset         = mMoveRange * Math::Sin(Math::ToRadians(mTheta));
    Transform* transform = mOwner->GetTransform();
    transform->SetWorldPosition(Vector3(mBasePosX, mBasePosY + offset, mBasePosZ));
    mTheta += 5.0f;
    switch (mStatus) {
    case PressAnyButtonMoveStatus::Init: {
        if (Input::GetButtonDown(1)
            || Input::GetButtonDown(2)
            || Input::GetButtonDown(3)
            || Input::GetButtonDown(4)
            || Input::GetButtonDown(5)
            || Input::GetButtonDown(6)
            || Input::GetButtonDown(7)
            || Input::GetButtonDown(8)
            || Input::GetButtonDown(9)
            || Input::GetButtonDown(10)
            || Input::GetButtonDown(11)
            || Input::GetButtonDown(12)) {
            // mStatus      = PressAnyButtonMoveStatus::GoMtaching;
            Audio::PlayChunk(mChunk_GoMatching);
            mActionFrame = 0;
            break;
        }
        mActionFrame++;
    } break;
    case PressAnyButtonMoveStatus::GoMtaching: {
        GoMatching(mActionFrame);
        mActionFrame++;
    } break;
    default:
        std::cout << "PressAnyButtonMoveStatus error" << std::endl;
        break;
    }
}
void PressAnyButtonMove::LateUpdate() { }

void PressAnyButtonMove::GoMatching(int frame)
{
    if (frame == 0) {
        Audio::PlayChunk(mChunk_GoMatching);
    }
}