#include "heroBody.h"
#include "../components/behaviour/heroBodyMove.h"
#include "hero.h"

HeroBody::HeroBody(Hero* hero, const std::string& tag)
    : GameObject("HeroBody", tag)
    , mHero(hero)
{
    SetBehaviour(new HeroBodyMove(this, mHero));
}