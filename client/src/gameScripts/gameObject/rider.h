#pragma once
#include "../../../../common/src/gameScripts/gameObject/rider.h"

class Hero;
class Rider_C : public Rider {
public:
    explicit Rider_C(Hero* hero, RiderType riderType);
    ~Rider_C() override = default;

private:
};