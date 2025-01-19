#include "playerInfo.h"

PlayerInfo::PlayerInfo()
    : id(0)
    , name("unknown")
{
    heroInfo.riderType = RiderType::BaseHuman;
    heroInfo.beyType   = BeyType::Shuriken;
}
PlayerInfo::PlayerInfo(int p_id, const char p_name[8], RiderType p_riderType, BeyType p_beyType)
    : id(p_id)
{
    strncpy(name, p_name, sizeof(name) - 1); // 安全にコピー
    name[sizeof(name) - 1] = '\0';           // 文字列の終端を保証
    heroInfo.riderType     = p_riderType;
    heroInfo.beyType       = p_beyType;
}