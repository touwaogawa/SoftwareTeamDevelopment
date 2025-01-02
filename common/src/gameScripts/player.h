#pragma once

#include "../../../common/src/gameObject.h"
#include "../commandData.h"
#include "hero/bey.h"
#include "hero/hero.h"
#include "hero/rider.h"
#include <deque>
struct PlayerInfo {
    int id;
    char name[8];
    HeroInfo heroInfo;

    PlayerInfo();
    PlayerInfo(int p_id, const char p_name[8], RiderType p_riderType, BeyType p_beyType);
};
class Player : public GameObject {
public:
    Player(Scene* scene, PlayerInfo playerInfo, const int* currentSceneFrame);
    ~Player() override;

    std::deque<CommandData> commandBuffer;
    CommandData prevCommandData;
    Hero* GetHero() const;
    int GetID() const;
    int GetCurrentSceneFrame() const;

private:
    PlayerInfo mPlayerInfo;
    Hero* mHero;

    const int* mCurrentSceneFrame;
};