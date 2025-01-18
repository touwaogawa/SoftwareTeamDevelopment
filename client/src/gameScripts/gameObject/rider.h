#pragma once
#include "../../../../common/src/gameScripts/gameObject/rider.h"
#include <string>

class Hero;
class Rider_C : public Rider {
public:
    Rider_C(Hero* hero, RiderType riderType, const std::string& tag, int playerID);
    ~Rider_C() override = default;

private:
};