#pragma once
#include "../../../../common/src/gameScripts/gameObject/hero.h"
#include "../../../../utils/src/math.h"
#include <string>

class HeroMove;
class Player;
class Hero_C : public Hero {
public:
    Hero_C(Player* player, HeroInfo heroInfo, Physics* physics, const std::string& tag);
    ~Hero_C() override = default;

private:
};