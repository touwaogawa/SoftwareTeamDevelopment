#pragma once
#include "../../../../common/src/gameObject.h"
#include <string>

enum class BeyType {
    Shuriken,
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
    Bey(class Scene* scene, class Transform* parent, BeyType beyType);
    ~Bey() override;

private:
    std::string RenderFileSelection(BeyType beyType);
    BeyBaseStatus mBeyBaseStatus;
};