#include "bey.h"
#include "../../../../common/src/component.h"
#include "../../components/transform.h"
#include "beyMove.h"
#include <iostream>
#include <string>
Bey::Bey(class Scene* scene, class Transform* parent, BeyType beyType)
    : GameObject(scene, parent, new BeyMove(this), GameObjectRenderType::Mesh3D, RenderFileSelection(beyType))
{
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
