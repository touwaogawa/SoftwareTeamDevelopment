#pragma once
#include "../../../../common/src/gameObject.h"
enum class BeyType {
    Shuriken,
    Hexagram,
    Snowflake,
    BeyTypeNum
};

struct BeyBaseStatus {
    float walkAcceleration = 0.05f;  // 歩行加速
    float maxWalkSpeed     = 0.1f;   // 最大歩行スピード
    float initialDushPower = 10.0f;  // ダッシュ初速度
    float DushPower        = 5.0f;   // ダッシュ加速量
    float maxRunSpeed      = 0.25f;  // 最大ダッシュ速度
    float traction         = 0.1f;   // 地上抵抗
    float mass             = 100.0f; // 質量
};

class Bey : public GameObject {
public:
    Bey(Scene* scene, Transform* parent, BeyType beyType, class BeyMove* beyMove);
    ~Bey() override;

private:
    BeyBaseStatus mBeyBaseStatus;
};