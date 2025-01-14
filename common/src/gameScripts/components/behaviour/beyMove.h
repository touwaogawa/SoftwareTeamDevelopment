#pragma once
#include "../../../component/behaviour.h"

class Bey;
class Hero;
class BeyMove : public Behaviour {
public:
    explicit BeyMove(Bey* owner);
    virtual ~BeyMove() override = default;

    void Start() override;
    void Update() override;
    void LateUpdate() override;

private:
    Bey* mBey;
    Hero* mHero;
    float mSpinPower;
    float mMinSpinPower;
};