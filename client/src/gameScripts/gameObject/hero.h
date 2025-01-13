#pragma once
#include "../../../../common/src/gameScripts/gameObject/hero.h"
#include "../../../../utils/src/math.h"

class HeroMove;
class Player;
class Hero_C : public Hero {
public:
    Hero_C(Player* player, HeroInfo heroInfo, Physics* physics);
    ~Hero_C() override = default;

private:
};