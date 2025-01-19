#pragma once
#include "../../../../../common/src/gameObject.h"
#include "../../../../../utils/src/math.h"
#include <string>

class KnockbackSmokeEffect : public GameObject {
public:
    explicit KnockbackSmokeEffect(Vector3 pos);
    ~KnockbackSmokeEffect() override = default;

private:
};