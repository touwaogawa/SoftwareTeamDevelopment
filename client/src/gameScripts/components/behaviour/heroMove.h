#pragma once
#include "../../../../../common/src/gameScripts/components/behaviour/heroMove.h"

class Hero;
class HeroMove_C : public HeroMove {
public:
    HeroMove_C(Hero* owner);
    ~HeroMove_C() override = default;

private:
};