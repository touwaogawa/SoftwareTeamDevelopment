#include "pressAnyButtonMove.h"
#include "../../../../../common/src/component/transform.h"
#include "../../../../../common/src/gameObject.h"
#include "../../../../../common/src/sceneManager.h"
#include "../../../../../utils/src/input.h"
#include "../../../../../utils/src/math.h"
#include "../../../audio.h"
#include "../../../component/camera.h"
#include "../../../component/spriteRenderer.h"
#include "../../scene/matching.h"
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
    , mSpriteColor(Vector3())
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
    mBaseScale        = mOwner->GetTransform()->GetWorldScale();
}
void PressAnyButtonMove::Update()
{
    std::cout << "PressAnyButtonMoveStatus update" << std::endl;
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
            mActionFrame = 0;
            Audio::PlayChunk(mChunk_GoMatching);
            mStatus = PressAnyButtonMoveStatus::GoMtaching;
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
    SpriteRenderer* sprite = mOwner->GetComponent<SpriteRenderer>();
    Transform* transform   = mOwner->GetTransform();
    if (frame == 0) {
        Audio::PlayChunk(mChunk_GoMatching);

        sprite->SetUseCustomColor(true);
        sprite->SetCustomColor(Vector3(0.5f, 0.5f, 0.5f));
        transform->SetWorldScale(mBaseScale * 0.95);
    }
    if (frame == 5) {
        transform->SetWorldScale(Vector3(mBaseScale));
        sprite->SetCustomColor(Vector3(1.0f, 1.0f, 1.0f));
    }
    if (frame > 60) {
        SceneManager::LoadScene(new MatchingScene());
    }
}