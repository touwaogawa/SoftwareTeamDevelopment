#pragma once
#include "../../../../common/src/gameObject.h"
#include "../../../../common/src/gameScripts/commandData.h"
#include "../../../../common/src/gameScripts/playerInfo.h"
#include "../../../../utils/src/math.h"
#include "bey.h"
#include "hero.h"
#include "rider.h"
#include <deque>
#include <string>

enum class PlayerState {
    Init,
    Battle,
    Defeat,
    PlayerStateNum
};

class Player : public GameObject {
public:
    Player(PlayerInfo playerInfo, const std::string& tag);
    ~Player() override = default;

    Hero* const GetHero() const { return mHero; }

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

private:
    PlayerInfo mPlayerInfo;
    PlayerState mPlayrState;
    Hero* const mHero;

    CommandData mCommandData;
    CommandData mPreCommandData;
};