#include "bey.h"
#include "../../component/meshRenderer.h"
#include "../components/behaviour/beyMove.h"
#include <iostream>

Bey_C::Bey_C(BeyType beyType)
    : Bey(beyType)
{
    SetBehaviour(new BeyMove_C(this));
    switch (beyType) {
    case BeyType::Shuriken:
        AddComponent(new MeshRenderer(this, "../assets/models/Shuriken.obj", "../assets/textures/silver.png"));
        break;
    case BeyType::Hexagram:
        AddComponent(new MeshRenderer(this, "../assets/models/Hexagram.obj", "../assets/textures/silver.png"));
        break;
    case BeyType::Snowflake:
        AddComponent(new MeshRenderer(this, "../assets/models/Snowflake.obj", "../assets/textures/silver.png"));
        break;
    default:
        std::cout << "BeyType error" << std::endl;
        break;
    }
}
