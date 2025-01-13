#pragma once
#include "../../../../../common/src/gameScripts/components/behaviour/riderMove.h"

class Rider;
class RiderMove_C : public RiderMove {
public:
    RiderMove_C(Rider* owner);
    ~RiderMove_C() override = default;

private:
};