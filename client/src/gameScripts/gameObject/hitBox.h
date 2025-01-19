#pragma once
#include "../../../../common/src/gameObject.h"
#include "../../../../utils/src/math.h"
#include <string>

class Hero;
class HitBox : public GameObject {
public:
    HitBox(Hero* ownerHero, const std::string& ignoreTag, float radius, Vector3 hitVector, float damage, int destroyFrame, int& actionFrame);
    ~HitBox() override = default;

private:
};