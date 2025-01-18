#pragma once
#include "../../../../../common/src/gameScripts/components/behaviour/heroMove.h"

class Hero;
class HeroMove_C : public HeroMove {
public:
    HeroMove_C(Hero* owner);
    ~HeroMove_C() override = default;

    void OnDamage(int stopFrame, int downFrame, rp3d::Vector3 vector) override;
    void HitOther(int stopFrame, float power) override;

private:
};