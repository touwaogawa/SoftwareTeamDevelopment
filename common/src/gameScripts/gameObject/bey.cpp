#include "bey.h"
#include "../components/behaviour/beyMove.h"
#include <iostream>

Bey::Bey(Scene* scene, Transform* parent, BeyType beyType, BeyMove* beyMove)
    : GameObject(scene, parent, beyMove)
{
    switch (beyType) {
    case BeyType::Shuriken:
        mBeyBaseStatus = {
            0.05f,
            0.1f,
            10.0f,
            5.0f,
            0.25f,
            0.1f,
            100.0f
        };
        break;
    default:
        std::cout << "BeyType error" << std::endl;
        mBeyBaseStatus = {
            0.05f,
            0.1f,
            10.0f,
            5.0f,
            0.25f,
            0.1f,
            100.0f
        };
        break;
    }
    // std::cout << "bey constructor" << std::endl;
}

Bey::~Bey()
{
}
