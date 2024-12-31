#pragma once

#include "../../../../utils/src/math.h"
#include "../../gameObject.h"
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
};

struct HeroCurrentStatus {
    HeroState state  = HeroState::Idle;     // 現在の状態
    Vector2 moveAxis = Vector2(0.0f, 0.0f); // 向いている方向(地面と水平方向)
    float speed      = 0.0f;
};
class Hero : public GameObject {
public:
    Hero(Scene* scene, Transform* parent, HeroBaseStatus heroBaseStatus = HeroBaseStatus());
    ~Hero() override;

    HeroCurrentStatus mCurrentStatus;

    float GetWalkAcceleration() const;
    float GetMaxWalkSpeed() const;
    float GetInitialDushSpeed() const;
    float GetDushAcceleration() const;
    float GetMaxRunSpeed() const;
    float GetTraction() const;

    class Bey* GetBey() const;
    class Rider* GetRider() const;

private:
    class Bey* mBey;
    class Rider* mRider;
    HeroBaseStatus mBaseStatus;
};