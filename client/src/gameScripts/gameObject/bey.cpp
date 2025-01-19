#include "bey.h"
#include "../../component/meshRenderer.h"
#include "../components/behaviour/beyMove.h"
#include "hero.h"
#include <iostream>

Bey::Bey(Hero* hero, BeyType beyType, const std::string& tag)
    : GameObject("Bey", tag)
    , mHero(hero)
{
    switch (beyType) {
    case BeyType::Shuriken:
        AddComponent(new MeshRenderer(this, "../assets/models/Shuriken.obj", "../assets/textures/silver.png"));
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
        AddComponent(new MeshRenderer(this, "../assets/models/Hexagram.obj", "../assets/textures/silver.png"));
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
        AddComponent(new MeshRenderer(this, "../assets/models/Snowflake.obj", "../assets/textures/silver.png"));
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
        AddComponent(new MeshRenderer(this, "../assets/models/Shuriken.obj", "../assets/textures/default.png"));
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
    SetBehaviour(new BeyMove(this, mHero));
}
