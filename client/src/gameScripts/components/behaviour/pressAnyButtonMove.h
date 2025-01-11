#pragma once
#include "../../../../../common/src/component/behaviour.h"
#include "../../../../../utils/src/math.h"

enum class PressAnyButtonMoveStatus {
    Init,
    GoMtaching,
    StatusNum
};

class PressAnyButtonMove : public Behaviour {
public:
    explicit PressAnyButtonMove(GameObject* owner);
    ~PressAnyButtonMove() override = default;

    void Start() override;
    void Update() override;
    void LateUpdate() override;

    void GoMatching(int frame);

private:
    PressAnyButtonMoveStatus mStatus;
    float mTheta;
    float mMoveRange;
    float mBasePosX;
    float mBasePosY;
    float mBasePosZ;
    int mActionFrame;
    class Mix_Chunk* mChunk_GoMatching;
    Vector3 mSpriteColor;
    Vector3 mBaseScale;
};