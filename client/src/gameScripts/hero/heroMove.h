#pragma once
#include "../../components/behaviour.h"
class HeroMove : public Behaviour {
public:
    explicit HeroMove(GameObject* owner);
    ~HeroMove() override = default;

    void Start() override;
    void Update() override;
    void LateUpdate() override;
    void Dush(float axis_x, float axis_y);

private:
    float mCurrentSpeed; // 現在の水平方向の移動速度
};