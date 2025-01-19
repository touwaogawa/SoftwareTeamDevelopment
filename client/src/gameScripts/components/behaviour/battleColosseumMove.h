#pragma once
#include "../../../../../common/src/component/behaviour.h"
#include "../../../../../utils/src/math.h"
#include <vector>

class Hero;
class BattleColosseumMove : public Behaviour {
public:
    explicit BattleColosseumMove(GameObject* owner);
    ~BattleColosseumMove() override = default;

    void Start() override;
    void Update() override;

private:
    const int mFinFrame;
    int mFrame;
    const Vector3 mInitialPos;
    const Vector3 mTargetPos;
    const Quaternion mInitialRot;
    const Quaternion mTargetRot;
};