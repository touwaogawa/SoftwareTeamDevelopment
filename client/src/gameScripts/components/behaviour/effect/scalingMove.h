#pragma once
#include "../../../../../../common/src/component/behaviour.h"
#include "../../../../../../utils/src/math.h"

class ScalingMove : public Behaviour {
public:
    ScalingMove(GameObject* owner, Vector3 scaleVelocity, int lifeFrame);
    virtual ~ScalingMove() override = default;

    void Update() override;

private:
    const Vector3 mScaleVelocity;
    const int mLifeFrame;
    int mFrame;
};