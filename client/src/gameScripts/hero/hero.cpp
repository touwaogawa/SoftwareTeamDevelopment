#include "hero.h"
#include "../../component.h"
#include "../../components/transform.h"
#include "bey.h"
#include "heroMove.h"

Helo::Helo(Scene* scene, Transform* parent)
    : GameObject(scene, parent, new HeroMove(this))
    , mBey(new Bey(mScene, mTransform))
{
}

Helo::~Helo()
{
}