#pragma once
#include "../../../../common/src/gameObject.h"
#include <string>

class Hero;
class Rider;
class Bey;

class HeroBody : public GameObject {
public:
    HeroBody(Hero* hero, const std::string& tag);
    ~HeroBody() override = default;

private:
    Hero* const mHero;
};