#pragma once
#include "../../../../../common/src/gameScripts/components/behaviour/playerMove.h"

class Player;
class PlayerMove_C : public PlayerMove {
public:
    PlayerMove_C(Player* owner);
    ~PlayerMove_C() override = default;

private:
    void DefeatedAction1() override;
    void DefeatedAction2() override;
    void DefeatedAction3Normal() override;
    void DefeatedAction3Special() override;
};