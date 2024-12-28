#include "player.h"
#include "hero/hero.h"
#include "playerMove.h"
Player::Player(Scene* scene, Transform* parent, int playerID)
    : GameObject(scene, parent, new PlayerMove(this))
    , mHero(new Hero(mScene, mTransform, 0.05f, 0.1f, 0.1f, 0.05f, 0.35f, 0.1f, 50.0f))
    , mID(playerID)
{
}
Player::~Player()
{
}

GameObject* Player::GetHero() const
{
    return mHero;
}
int Player::GetID() const
{
    return mID;
}