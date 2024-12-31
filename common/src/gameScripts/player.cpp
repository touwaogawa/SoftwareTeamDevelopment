#include "player.h"
#include "hero/hero.h"
#include "playerMove.h"
Player::Player(Scene* scene, Transform* parent, int playerID, const int* currentSceneFrame)
    : GameObject(scene, parent, new PlayerMove(this))
    , mHero(new Hero(mScene, mTransform))
    , mID(playerID)
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
    return mID;
}
int Player::GetCurrentSceneFrame() const
{
    return *mCurrentSceneFrame;
}