#pragma once
#include "../../../../common/src/gameObject.h"
#include "../../../../common/src/gameScripts/beyInfo.h"
#include <string>

class BeyMove;
class Hero;

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
    Bey(Hero* hero, BeyType beyType, const std::string& tag);
    ~Bey() override = default;
    Hero* const GetHero() const { return mHero; }

private:
    BeyBaseStatus mBeyBaseStatus;
    Hero* const mHero;
};