#pragma once

#include "../../gameObject.h"

enum class HeroStatus {
    Idle,
    Walking,
    Dash,

};
class Hero : public GameObject {
public:
    Hero(Scene* scene, Transform* parent,
        float walkAcceleration = 1.0f,
        float maxWalkSpeed     = 1.0f,
        float initialDushSpeed = 1.0f,
        float dushAcceleration = 1.0f,
        float maxRunSpeed      = 1.0f,
        float traction         = 1.0f);
    ~Hero() override;
    HeroStatus GetStatus() const;
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

    HeroStatus mHeroStatus;
};