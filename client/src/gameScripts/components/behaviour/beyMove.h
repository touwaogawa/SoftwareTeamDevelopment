#pragma once
#include "../../../../../common/src/gameScripts/components/behaviour/beyMove.h"

class Bey;
class BeyMove_C : public BeyMove {
public:
    explicit BeyMove_C(Bey* owner);
    ~BeyMove_C() override = default;

private:
};