#pragma once
#include "../../../../../common/src/component/behaviour.h"
#include "../../../../../utils/src/math.h"
class Player;
class Hero;

class PlayerMove : public Behaviour {
public:
    explicit PlayerMove(Player* owner, Hero* hero);
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
    Player* const mPlayer;
    Hero* const mHero;
    int mCommandDelay;
    Vector2 mMoveAxisNorm;
    float mStickDeadZone;

    void InitUpdate();
    void BattleUpdate();
    void DefeatedUpdate();
};