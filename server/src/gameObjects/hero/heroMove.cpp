#include "heroMove.h"
#include <iostream>
HeroMove_S::HeroMove_S(GameObject* owner)
    : HeroMove(owner)
{
    std::cout << "heroMove_s constructer" << std::endl;
}