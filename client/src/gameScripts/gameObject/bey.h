#pragma once
#include "../../../../common/src/gameScripts/gameObject/bey.h"
#include <string>

class Hero;
class Bey_C : public Bey {
public:
    explicit Bey_C(Hero* hero, BeyType beyType, const std::string& tag);
    ~Bey_C() override = default;

private:
};