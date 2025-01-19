#pragma once
#include "heroInfo.h"
#include <cstring>

struct PlayerInfo {
    int id;
    char name[8];
    HeroInfo heroInfo;
    PlayerInfo();
    PlayerInfo(int p_id, const char p_name[8], RiderType p_riderType, BeyType p_beyType);
};
