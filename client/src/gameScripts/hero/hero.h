#pragma once

#include "../../gameObject.h"
#include "../../math.h"
enum class HeroStatus {
    Idle,
    Walking,
    StartRunning,
    Running,
    StopRunning,
    RunningAttack,
    PreJump

};
class Hero : public GameObject {
public:
    Hero(Scene* scene, Transform* parent,
        float walkAcceleration = 0.05f,
        float maxWalkSpeed     = 0.1f,
        float initialDushSpeed = 0.1f,
        float dushAcceleration = 0.05f,
        float maxRunSpeed      = 0.25f,
        float traction         = 0.1f,
        float mass             = 50.0f);
    ~Hero() override;

    HeroStatus currentStatus; // 状態
    Vector2 currentMoveAxis;  // 移動方向
    float currentSpeed;       // 現在の水平方向の移動速度

    float GetWalkAcceleration() const;
    float GetMaxWalkSpeed() const;
    float GetInitialDushSpeed() const;
    float GetDushAcceleration() const;
    float GetMaxRunSpeed() const;
    float GetTraction() const;

private:
    GameObject* mBey;
    GameObject* mRider;

    float mWalkAcceleration; // 歩行加速
    float mMaxWalkSpeed;     // 最大歩行スピード
    float mInitialDushSpeed; // ダッシュ初速度
    float mDushAcceleration; // ダッシュ加速量
    float mMaxRunSpeed;      // 最大ダッシュ速度
    float mTraction;         // 地上抵抗
    float mMass;             // 質量
};