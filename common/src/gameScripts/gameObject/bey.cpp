#include "bey.h"
#include "../components/behaviour/beyMove.h"
#include <iostream>

Bey::Bey(BeyType beyType)
    : GameObject()
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
    case BeyType::Hexagram:
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
    case BeyType::Snowflake:
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
