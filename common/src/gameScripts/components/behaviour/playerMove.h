#pragma once
#include "../../../component/behaviour.h"

class Player;
class Hero;

class PlayerMove : public Behaviour {
public:
    explicit PlayerMove(Player* owner);
    virtual ~PlayerMove() override = default;

    void Start() override;
    void Update() override;
    void LateUpdate() override;

    virtual void DefeatedAction1() { }
    virtual void DefeatedAction2() { }
    void DefeatedAction3();
    virtual void DefeatedAction3Normal() { }
    virtual void DefeatedAction3Special() { }

private:
    Player* mPlayer;
    Hero* mHero;

    void
    InitUpdate();
    void BattleUpdate();
    void DefeatedUpdate();
};