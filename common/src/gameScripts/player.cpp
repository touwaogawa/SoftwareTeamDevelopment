#include "player.h"
#include "hero/hero.h"
#include "playerMove.h"
Player::Player(Scene* scene, Transform* parent, int playerID)
    : GameObject(scene, parent, new PlayerMove(this))
    , mHero(new Hero(mScene, mTransform))
    , mID(playerID)
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