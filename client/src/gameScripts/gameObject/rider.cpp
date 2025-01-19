#include "rider.h"
#include "../../component/meshRenderer.h"
#include "../components/behaviour/riderMove.h"
#include "hero.h"
#include <iostream>
Rider::Rider(Hero* hero, RiderType riderType, const std::string& tag, int playerID)
    : GameObject("Rider", tag)
    , mHero(hero)
{
    std::string texture;
    switch (riderType) {
    case RiderType::BaseHuman:
        switch (playerID) {
        case 0: {
            texture = "../assets/textures/humanColor_red.png";
        } break;
        case 1: {
            texture = "../assets/textures/humanColor_blue.png";
        } break;
        case 2: {
            texture = "../assets/textures/humanColor_green.png";
        } break;
        case 3: {
            texture = "../assets/textures/humanColor_yellow.png";
        } break;
        default: {
            texture = "../assets/textures/humanColor.png";
            // std::cout << "rider : playerID error" << std::endl;
        }
        }
        AddComponent(new MeshRenderer(this, "../assets/models/BaseHuman.obj", texture));

        break;
    default:
        std::cout << "RiderType error" << std::endl;
        break;
    }

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
    SetBehaviour(new RiderMove(this, mHero));
}
