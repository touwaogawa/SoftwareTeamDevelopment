#pragma once
#include "../../../component/behaviour.h"

class Rider;
class RiderMove : public Behaviour {
public:
    explicit RiderMove(Rider* owner);
    virtual ~RiderMove() override = default;

    void Start() override;
    void Update() override;
    void LateUpdate() override;

private:
    Rider* mRider;
    float dir_x;
    float dir_y;
};