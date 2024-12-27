#pragma once
#include "../../components/behaviour.h"
class HeroMove : public Behaviour {
public:
    explicit HeroMove(GameObject* owner);
    ~HeroMove() override = default;

    void Start() override;
    void Update() override;
    void LateUpdate() override;

private:
    void UpdatePosision();
    class Hero* mHero;
};