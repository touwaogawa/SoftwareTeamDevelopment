#include "rider.h"
#include "../components/behaviour/riderMove.h"
#include <iostream>

Rider::Rider(Scene* scene, Transform* parent, RiderType riderType, RiderMove* riderMove)
    : GameObject(scene, parent, riderMove)
{
    switch (riderType) {
    case RiderType::BaseHuman:
        mRiderBaseStatus = {
            50.0f
        };
        break;
    default:
        std::cout << "RiderType error" << std::endl;
        break;
    }
    std::cout << "rider constructer" << std::endl;
}

Rider::~Rider()
{
}
