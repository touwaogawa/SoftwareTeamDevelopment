#pragma once
// これ何とかしたい
#include "../../../../utils/src/math.h"
#include "../../gameObject.h"
#include "bey.h"
#include "rider.h"
#include <string>

class Physics;
class Player;
enum class HeroState {
    Idle,
    Walking,
    Running,
    PreRunningAttack, //
    RunningAttack,
    AfterRunningAttack,
    PreFallAttack, //
    FallAttack,
    AfterFallAttack,
    PreAirFrontAttack, //
    AirFrontAttack,
    AfterAirFrontAttack,
    PreAirBackAttack, //
    AirBackAttack,
    AfterAirBackAttack,
    PreJump,
    BigJump,
    SmallJump,
    AirIdle,
    AirMove,
    AirPreJump,
    KnockBack,
    Death,
    HeroStateNum

};
struct HeroBaseStatus {
    float mass               = 50.0f; // 質量
    float walkAcceleration   = 4.0f;  // 歩行加速
    float maxWalkSpeed       = 4.0f;  // 最大歩行スピード
    float initialDushSpeed   = 3.0f;  // ダッシュ初速度
    float dushAcceleration   = 1.5f;  // ダッシュ加速量
    float maxDushSpeed       = 10.5f; // 最大ダッシュ速度
    float traction           = 0.9f;  // 地上抵抗
    float airAcceleration    = 5.0f;  // 空中加速
    float maxAirSpeed        = 1.0f;  // 空中最大速度
    float airFriction        = 4.0f;  // 空中抵抗
    float maxFallSpeed       = 3.0f;  // 最大落下速度
    float fastFallSpeed      = 5.0f;  // 急降下速度
    float fullJumpVelocity   = 9.0f;  // 大ジャンプ初速度
    float shortJumpVelocity  = 4.0f;  // 小ジャンプ初速度
    float doubleJumpVelocity = 9.0f;  // 2段ジャンプ初速
};

struct HeroCurrentStatus {
    HeroState state  = HeroState::Idle;     // 現在の状態
    Vector2 faceDir  = Vector2(0.0f, 0.0f); // 顔の方向(Normalized or 0)
    Vector2 velocity = Vector2(0.0f, 0.0f);
    int actionFrame  = 0;
    int stopFrame    = 0;
    int downFrame    = 0;
    int airJumpCount = 0;
};

struct HeroInfo {
    RiderType riderType;
    BeyType beyType;
};

class Hero : public GameObject {
public:
    Hero(Player* player, HeroInfo heroInfo, Physics* physics, const std::string& tag);
    virtual ~Hero() override = default;

    HeroCurrentStatus mCurrentStatus;

    void SetState(HeroState heroState)
    {
        mCurrentStatus.state       = heroState;
        mCurrentStatus.actionFrame = 0;
    }
    HeroState GetState() const { return mCurrentStatus.state; }

    const HeroBaseStatus& GetBaseStatus() const { return mBaseStatus; }

    Player* GetPlayer() const { return mPlayer; }

    Bey* GetBey() const { return mBey; }
    void SetBey(Bey* bey) { mBey = bey; }

    Rider* GetRider() const { return mRider; }
    void SetRider(Rider* rider) { mRider = rider; }

protected:
    HeroInfo mHeroInfo;
    HeroBaseStatus mBaseStatus;
    Player* const mPlayer;
    Rider* mRider;
    Bey* mBey;
};