#pragma once
#include "../../../../../common/src/component/behaviour.h"

class Bey;
class Hero;
class BeyMove : public Behaviour {
public:
    explicit BeyMove(Bey* owner, Hero* hero);
    virtual ~BeyMove() override = default;

    void Start() override;
    void Update() override;
    void LateUpdate() override;

private:
    Bey* const mBey;
    Hero* const mHero;
    float mSpinPower;
    float mMinSpinPower;
};