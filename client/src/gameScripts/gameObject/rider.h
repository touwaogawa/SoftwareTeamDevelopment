#pragma once
#include "../../../../common/src/gameScripts/gameObject/rider.h"
#include <string>

class Hero;
class Rider_C : public Rider {
public:
    explicit Rider_C(Hero* hero, RiderType riderType, const std::string& tag);
    ~Rider_C() override = default;

private:
};