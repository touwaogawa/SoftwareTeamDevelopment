#pragma once

#include "../commandData.h"
#include "../gameObject.h"
#include <deque>

class Player : public GameObject {
public:
    Player(Scene* scene, Transform* parent);
    ~Player() override;

    std::deque<CommandData> commandBuffer;
    float walkAcceleration; // 歩行加速
    float maxWalkSpeed;     // 最大歩行スピード
    float initialDushSpeed; // ダッシュ初速度
    float dushAcceleration; // ダッシュ加速量
    float maxRunSpeed;      // 最大ダッシュ速度
    float Traction;         // 地上抵抗

private:
    GameObject* mHero;
    int mID;
};