#pragma once
#include "../../../component/behaviour.h"

class Player;
class PlayerMove : public Behaviour {
public:
    explicit PlayerMove(Player* owner);
    virtual ~PlayerMove() override = default;

    void Start() override;
    void Update() override;
    void LateUpdate() override;

private:
    class Player* mPlayer;
    class Hero* mHero;
};