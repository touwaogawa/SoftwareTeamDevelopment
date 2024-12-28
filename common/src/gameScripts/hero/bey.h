#pragma once
#include "../../../../common/src/gameObject.h"

class Bey : public GameObject {
public:
    Bey(class Scene* scene, class Transform* parent,
        float mass             = 1.0f,
        float walkAcceleration = 1.0f,
        float maxWalkSpeed     = 1.0f,
        float initialDushSpeed = 1.0f,
        float dushAcceleration = 1.0f,
        float maxRunSpeed      = 1.0f,
        float traction         = 1.0f);
    ~Bey() override;

private:
    float mMass;             // 質量
    float mWalkAcceleration; // 歩行加速
    float mMaxWalkSpeed;     // 最大歩行スピード
    float mInitialDushSpeed; // ダッシュ初速度
    float mDushAcceleration; // ダッシュ加速量
    float mMaxRunSpeed;      // 最大ダッシュ速度
    float mTraction;         // 地上抵抗
    class MeshRenderer* mMeshRenderer;
};