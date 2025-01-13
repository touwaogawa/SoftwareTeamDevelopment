#pragma once
#include "../../../component/behaviour.h"
class RiderMove : public Behaviour {
public:
    explicit RiderMove(GameObject* owner);
    virtual ~RiderMove() override = default;

    void Start() override;
    void Update() override;
    void LateUpdate() override;

private:
    float dir_x;
    float dir_y;
};