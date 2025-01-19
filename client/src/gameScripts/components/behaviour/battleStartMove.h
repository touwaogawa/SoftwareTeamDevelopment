#pragma once
#include "../../../../../common/src/component/behaviour.h"
#include "../../../../../utils/src/math.h"
#include <vector>

class Hero;
class BattleStartMove : public Behaviour {
public:
    explicit BattleStartMove(GameObject* owner);
    ~BattleStartMove() override = default;

    void Start() override;
    void Update() override;

private:
    float x;
    bool md;
};