#include "hero.h"
#include "../components/behaviour/heroMove.h"
#include "bey.h"
#include "rider.h"

Hero_C::Hero_C(Player* player, HeroInfo heroInfo, Physics* physics)
    : Hero(player, heroInfo, physics)
{
}
