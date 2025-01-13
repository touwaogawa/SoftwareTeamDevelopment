#include "rider.h"
#include "../components/behaviour/riderMove.h"
#include <iostream>

Rider::Rider(Hero* hero, RiderType riderType)
    : GameObject()
    , mHero(hero)
{
    switch (riderType) {
    case RiderType::BaseHuman:
        mRiderBaseStatus = {
            50.0f
        };
        break;
    default:
        std::cout << "RiderType error" << std::endl;
        mRiderBaseStatus = {
            50.0f
        };
        break;
    }
    // std::cout << "rider constructor" << std::endl;
}
