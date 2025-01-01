#include "player.h"
#include "hero/hero.h"
#include "playerMove.h"
PlayerInfo::PlayerInfo(int p_id, const char p_name[8], RiderType p_riderType, BeyType p_beyType)
    : id(p_id)
{
    strncpy(name, p_name, sizeof(name) - 1); // 安全にコピー
    name[sizeof(name) - 1] = '\0';           // 文字列の終端を保証
    heroInfo.riderType     = p_riderType;
    heroInfo.beyType       = p_beyType;
}
Player::Player(Scene* scene, PlayerInfo playerInfo, const int* currentSceneFrame)
    : GameObject(scene, nullptr, new PlayerMove(this))
    , mPlayerInfo(playerInfo)
    , mHero(new Hero(mScene, mTransform, mPlayerInfo.heroInfo))
    , mCurrentSceneFrame(currentSceneFrame)
{
}

Player::~Player()
{
}

Hero* Player::GetHero() const
{
    return mHero;
}
int Player::GetID() const
{
    return mPlayerInfo.id;
}
int Player::GetCurrentSceneFrame() const
{
    return *mCurrentSceneFrame;
}