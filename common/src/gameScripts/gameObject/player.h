#pragma once
#include "../../../../common/src/gameObject.h"
#include "../../../../utils/src/math.h"
#include "../commandData.h"
#include "bey.h"
#include "hero.h"
#include "rider.h"
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
    explicit Player(PlayerInfo playerInfo);
    ~Player() override;

    std::deque<CommandData> commandBuffer;
    CommandData prevCommandData;

    Hero* GetHero() const { return mHero; }
    void SetHero(Hero* hero) { mHero = hero; }

    int GetID() const { return mPlayerInfo.id; }

protected:
    PlayerInfo mPlayerInfo;
    Hero* mHero;
};