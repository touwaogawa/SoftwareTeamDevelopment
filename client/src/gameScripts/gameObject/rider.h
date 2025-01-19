#pragma once
#include "../../../../common/src/gameObject.h"
#include "../../../../common/src/gameScripts/riderInfo.h"
#include <string>

class RiderMove;
class Hero;

struct RiderBaseStatus {
    float mass = 50.0f; // 質量
};

class Rider : public GameObject {
public:
    Rider(Hero* hero, RiderType riderType, const std::string& tag, int playerID);
    ~Rider() override = default;
    Hero* const GetHero() const { return mHero; }

private:
    RiderBaseStatus mRiderBaseStatus;
    Hero* const mHero;
};