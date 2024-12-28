#pragma once
#include "../../components/behaviour.h"
class RiderMove : public Behaviour {
public:
    explicit RiderMove(GameObject* owner);
    ~RiderMove() override = default;

    void Start() override;
    void Update() override;
    void LateUpdate() override;

private:
    float dir_x;
    float dir_y;
};