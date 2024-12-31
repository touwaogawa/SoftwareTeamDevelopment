#pragma once
#include "../components/behaviour.h"
class PlayerMove : public Behaviour {
public:
    explicit PlayerMove(GameObject* owner);
    ~PlayerMove() override = default;

    void Start() override;
    void Update() override;
    void LateUpdate() override;

private:
    class Player* mPlayer;
    class Hero* mHero;
    class HeroMove* mHeroMove;
};