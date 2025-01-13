#pragma once
// これ何とかしたい
#include "../../../../utils/src/math.h"
#include "../../gameObject.h"
#include "bey.h"
#include "rider.h"

class Physics;
class Player;
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
    float WalkSpeed        = 0.1f * 60.0f;  // 最大歩行スピード
    float initialDushSpeed = 0.1f * 60.0f;  // ダッシュ初速度
    float dushAcceleration = 0.05f * 60.0f; // ダッシュ加速量
    float maxDushSpeed     = 0.25f * 60.0f; // 最大ダッシュ速度
    float traction         = 0.1f;          // 地上抵抗
    float mass             = 50.0f;         // 質量
    float gravity          = 9.8f;          // 重力
};

struct HeroCurrentStatus {
    HeroState state = HeroState::Idle;     // 現在の状態
    Vector2 moveDir = Vector2(0.0f, 0.0f); // 移動している方向
    // float speed     = 0.0f;
};

struct HeroInfo {
    RiderType riderType;
    BeyType beyType;
};

class Hero : public GameObject {
public:
    Hero(Player* player, HeroInfo heroInfo, Physics* physics);
    ~Hero() override = default;

    HeroCurrentStatus mCurrentStatus;

    const HeroBaseStatus& GetBaseStatus() const { return mBaseStatus; }

    Player* GetPlayer() const { return mPlayer; }

    Bey* GetBey() const { return mBey; }
    void SetBey(Bey* bey) { mBey = bey; }

    Rider* GetRider() const { return mRider; }
    void SetRider(Rider* rider) { mRider = rider; }

protected:
    HeroInfo mHeroInfo;
    HeroBaseStatus mBaseStatus;
    Player* mPlayer;
    Rider* mRider;
    Bey* mBey;
};