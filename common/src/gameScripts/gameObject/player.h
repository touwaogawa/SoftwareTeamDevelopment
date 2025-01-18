#pragma once
#include "../../../../common/src/gameObject.h"
#include "../../../../utils/src/math.h"
#include "../commandData.h"
#include "bey.h"
#include "hero.h"
#include "rider.h"
#include <deque>
#include <string>

struct PlayerInfo {
    int id;
    char name[8];
    HeroInfo heroInfo;

    PlayerInfo();
    PlayerInfo(int p_id, const char p_name[8], RiderType p_riderType, BeyType p_beyType);
};

enum class PlayerState {
    Init,
    Battle,
    Defeat,
    PlayerStateNum
};

class Player : public GameObject {
public:
    explicit Player(PlayerInfo playerInfo, const std::string& tag);
    virtual ~Player() override = default;

    Hero* const GetHero() const { return mHero; }
    void SetHero(Hero* hero) { mHero = hero; }

    int GetID() const { return mPlayerInfo.id; }

    void SetPlayerState(PlayerState playerState) { mPlayrState = playerState; }
    PlayerState GetPlayerState() const { return mPlayrState; }

    const CommandData& GetCommandData() const { return mCommandData; }
    void SetCommandData(CommandData commandData)
    {
        mPreCommandData = mCommandData;
        mCommandData    = commandData;
    }

    const CommandData& GetPreCommandData() const { return mPreCommandData; }

protected:
    PlayerInfo mPlayerInfo;
    Hero* mHero;
    PlayerState mPlayrState;

    CommandData mCommandData;
    CommandData mPreCommandData;
};