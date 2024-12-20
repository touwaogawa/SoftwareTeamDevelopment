#include "player.h"
#include "hero/hero.h"
#include "playerMove.h"
Player::Player(Scene* scene, Transform* parent)
    : GameObject(scene, parent, new PlayerMove(this))
    , mHero(new Hero(mScene, mTransform))
{
}
Player::~Player()
{
}