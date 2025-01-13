#pragma once
#include "../../../../common/src/gameObject.h"

class RiderMove;
class Hero;
enum class RiderType {
    BaseHuman,
    RiderTypeNum
};

struct RiderBaseStatus {
    float mass = 50.0f; // 質量
};

class Rider : public GameObject {
public:
    explicit Rider(Hero* hero, RiderType riderType);
    ~Rider() override = default;
    Hero* GetHero() const { return mHero; }

protected:
private:
    RiderBaseStatus mRiderBaseStatus;
    Hero* mHero;
};