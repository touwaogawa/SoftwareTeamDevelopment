#pragma once
#include "../../../component/behaviour.h"

class Rider;
class Hero;
class RiderMove : public Behaviour {
public:
    explicit RiderMove(Rider* owner);
    virtual ~RiderMove() override = default;

    void Start() override;
    void Update() override;
    void LateUpdate() override;

private:
    Rider* mRider;
    Hero* mHero;
    float dir_x;
    float dir_y;
};