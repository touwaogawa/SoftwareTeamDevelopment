#include "battleColosseumMove.h"
#include "../../../../../common/src/component/transform.h"
#include "../../../../../utils/src/math.h"
#include "../../../audio.h"

BattleColosseumMove::BattleColosseumMove(GameObject* owner)
    : Behaviour(owner)
    , mFinFrame(60 * 4)
    , mFrame(0)
    , mInitialPos(Vector3(0.0f, -20.0f, 0.0f))
    , mTargetPos(Vector3(0.0f, -40.0f, 0.0f))
    , mInitialRot(Quaternion(Vector3::UnitY, Math::PiOver2))
    , mTargetRot(Quaternion::Identity)
{
}

void BattleColosseumMove::Start()
{
    Audio::PlayChunk("../assets/sounds/se/崖崩れ_4sec.mp3");
    Audio::PlayChunk("../assets/sounds/se/巨大モーター起動_4sec.mp3");
}

void BattleColosseumMove::Update()
{

    if (mFrame < mFinFrame) {
        Vector3 pos    = Vector3::Lerp(mInitialPos, mTargetPos, static_cast<float>(mFrame) / mFinFrame);
        Quaternion rot = Quaternion::Lerp(mInitialRot, mTargetRot, static_cast<float>(mFrame) / mFinFrame);
        GetTransform()->SetWorldPosition(pos);
        GetTransform()->SetLocalRotation(rot);
    } else if (mFrame == mFinFrame) {
        Audio::PlayChunk("../assets/sounds/se/巨大ロボットが倒れる.mp3");
        SetEnabled(false);
    }
    mFrame++;
}