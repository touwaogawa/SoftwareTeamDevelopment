#pragma once
#include "../../../component/behaviour.h"

class Vector2;
class HeroMove : public Behaviour {
public:
    explicit HeroMove(GameObject* owner);
    ~HeroMove() override = default;

    void Start() override;
    void Update() override;
    void LateUpdate() override;

    void Walking(Vector2 axis);
    void StartRunning(Vector2 axis);
    void Running(Vector2 axis);
    void StopRunning(Vector2 axis);
    void StartRunningAttack(Vector2 axis);
    bool UpdateRunningAttack();

private:
    void UpdatePosision();
    class Hero* mHero;
    int mCurrentActionFrame;
};