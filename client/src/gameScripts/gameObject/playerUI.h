#pragma once
#include "../../../../common/src/gameObject.h"
#include "../../../../utils/src/math.h"
#include <string>

class PlayerUI : public GameObject {
public:
    explicit PlayerUI(int playerID);
    ~PlayerUI() override = default;
};