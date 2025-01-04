#pragma once
#include "../../../component/behaviour.h"
class BeyMove : public Behaviour {
public:
    explicit BeyMove(GameObject* owner);
    ~BeyMove() override = default;

    void Start() override;
    void Update() override;
    void LateUpdate() override;

private:
    float mSpinPower;
    float mMinSpinPower;
};