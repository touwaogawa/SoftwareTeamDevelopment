#pragma once

#include "../../../../utils/src/math.h"
#include "../../gameObject.h"
#include "bey.h"
#include "rider.h"

enum class HeroState {
    Idle,
    Walking,
    StartRunning,
    Running,
    StopRunning,
    RunningAttack,
    PreJump,
    HeroStateNum

};
struct HeroBaseStatus {
    float walkAcceleration = 0.05f; // 歩行加速
    float maxWalkSpeed     = 0.1f;  // 最大歩行スピード
    float initialDushSpeed = 0.1f;  // ダッシュ初速度
    float dushAcceleration = 0.05f; // ダッシュ加速量
    float maxRunSpeed      = 0.25f; // 最大ダッシュ速度
    float traction         = 0.1f;  // 地上抵抗
    float mass             = 50.0f; // 質量
    float gravity          = 9.8f;  // 重力
};

struct HeroCurrentStatus {
    HeroState state  = HeroState::Idle;     // 現在の状態
    Vector2 moveAxis = Vector2(0.0f, 0.0f); // 向いている方向(地面と水平方向)
    float speed      = 0.0f;
};

struct HeroInfo {
    RiderType riderType;
    BeyType beyType;
};
class Hero : public GameObject {
public:
    Hero(Scene* scene, Transform* parent, HeroInfo heroInfo);
    ~Hero() override;

    HeroCurrentStatus mCurrentStatus;

    float GetWalkAcceleration() const;
    float GetMaxWalkSpeed() const;
    float GetInitialDushSpeed() const;
    float GetDushAcceleration() const;
    float GetMaxRunSpeed() const;
    float GetTraction() const;
    float GetMass() const;
    float GetGravity() const;

    Bey* GetBey() const;
    Rider* GetRider() const;

private:
    HeroInfo mHeroInfo;
    Rider* mRider;
    Bey* mBey;
    HeroBaseStatus mBaseStatus;
};