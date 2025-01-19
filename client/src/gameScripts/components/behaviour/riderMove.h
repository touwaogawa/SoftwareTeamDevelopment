#pragma once
#include "../../../../../common/src/component/behaviour.h"

class Rider;
class Hero;
class RiderMove : public Behaviour {
public:
    explicit RiderMove(Rider* owner, Hero* hero);
    virtual ~RiderMove() override = default;

    void Start() override;
    void Update() override;
    void LateUpdate() override;

private:
    Rider* const mRider;
    Hero* const mHero;
    float dir_x;
    float dir_y;
};