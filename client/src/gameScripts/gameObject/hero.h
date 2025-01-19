#pragma once

#include "../../../../common/src/gameObject.h"
#include "../../../../common/src/gameScripts/heroInfo.h"
#include "../../../../utils/src/math.h"
#include "bey.h"
#include "rider.h"
#include <string>

class Physics;
class Player;
class HeroBody;

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
    HeroState state   = HeroState::Idle;      // 現在の状態
    Vector2 faceDir   = Vector2(0.0f, -1.0f); // 顔の方向(Normalized or 0)
    Vector2 velocity  = Vector2(0.0f, 0.0f);
    int actionFrame   = 0;
    int stopFrame     = 0;
    int knockbackTime = 0;
    int airJumpCount  = 0;
    bool onGround     = true;
    float damageSum   = 0.0f;
};

class Hero : public GameObject {
public:
    Hero(Player* player, HeroInfo heroInfo, const std::string& tag);
    ~Hero() override = default;

    HeroCurrentStatus mCurrentStatus;

    void SetState(HeroState heroState)
    {
        mCurrentStatus.state       = heroState;
        mCurrentStatus.actionFrame = -1;
    }
    HeroState GetState() const { return mCurrentStatus.state; }

    const HeroBaseStatus& GetBaseStatus() const { return mBaseStatus; }

    Player* const GetPlayer() const { return mPlayer; }

    Bey* const GetBey() const { return mBey; }

    Rider* const GetRider() const { return mRider; }

private:
    HeroInfo mHeroInfo;
    HeroBaseStatus mBaseStatus;

    Player* const mPlayer;
    Rider* const mRider;
    Bey* const mBey;
    HeroBody* const mHeroBody;
};