#include "rider.h"
#include "../../component/meshRenderer.h"
#include "../components/behaviour/riderMove.h"
#include <iostream>
#include <string>
Rider_C::Rider_C(Hero* hero, RiderType riderType, const std::string& tag, int playerID)
    : Rider(hero, riderType, tag)
{
    // std::cout << "Rider_C constructer" << std::endl;
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
            std::cout << "rider : playerID error" << std::endl;
        }
        }
        AddComponent(new MeshRenderer(this, "../assets/models/BaseHuman.obj", texture));
        break;
    default:
        std::cout << "RiderType error" << std::endl;
        break;
    }
}
