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
    Player(Scene* scene, PlayerInfo playerInfo, const int* currentSceneFrame, class PlayerMove* playerMove);
    ~Player() override;

    std::deque<CommandData> commandBuffer;
    CommandData prevCommandData;
    Hero* GetHero() const;
    int GetID() const;
    int GetCurrentSceneFrame() const;

protected:
    PlayerInfo mPlayerInfo;
    Hero* mHero;
    const int* mCurrentSceneFrame;

    Vector3 GetInitialHeroPos(int id);
};