#include "bey.h"
#include "../../../../common/src/component.h"
#include "../../components/transform.h"
#include "beyMove.h"
#include <iostream>
#include <string>
Bey::Bey(class Scene* scene, class Transform* parent, BeyType beyType)
    : GameObject(scene, parent, new BeyMove(this), GameObjectRenderType::Mesh3D, RenderFileSelection(beyType))
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
        break;
    }
}

Bey::~Bey()
{
}

std::string Bey::RenderFileSelection(BeyType beyType)
{
    std::string renderFile;
    switch (beyType) {
    case BeyType::Shuriken:
        renderFile = "../assets/models/Shuriken.obj";
        break;
    default:
        std::cout << "BeyType error" << std::endl;
        break;
    }
    return renderFile;
}
