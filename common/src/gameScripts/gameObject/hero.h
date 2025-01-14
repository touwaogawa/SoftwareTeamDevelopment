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
    StartRunning,
    Running,
    StopRunning,
    RunningAttack,
    PreJump,
    BigJump,
    SmallJump,
    AirIdle,
    KnockBack,
    HitStop,
    Death,
    HeroStateNum

};
struct HeroBaseStatus {
    float WalkSpeed         = 4.0f;  // 最大歩行スピード
    float initialDushSpeed  = 3.0f;  // ダッシュ初速度
    float dushAcceleration  = 1.5f;  // ダッシュ加速量
    float maxDushSpeed      = 10.5f; // 最大ダッシュ速度
    float traction          = 0.9f;  // 地上抵抗
    float mass              = 50.0f; // 質量
    float bigJumpVelocity   = 4.0f;
    float smallJumpVelocity = 2.0f;
    float airMoveSpeed      = 1.0f;
    float attackSpeed       = 23.0f;
};

struct HeroCurrentStatus {
    HeroState state = HeroState::Idle;     // 現在の状態
    Vector2 moveDir = Vector2(0.0f, 0.0f); // 移動している方向
    Vector2 faceDir = Vector2(0.0f, 0.0f); // 顔のほうこう
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
        mCurrentStatus.state = heroState;
        mActionFrame         = 0;
    }
    HeroState GetState() const { return mCurrentStatus.state; }

    int mActionFrame;
    int mStopFrame;
    int mDownFrame;

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