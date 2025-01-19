#include "heroBody.h"
#include "hero.h"

HeroBody::HeroBody(Hero* hero, const std::string& tag)
    : GameObject("HeroBody", tag)
    , mHero(hero)
{
}