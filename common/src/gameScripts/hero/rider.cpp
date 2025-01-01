#include "rider.h"
#include "../../../../common/src/component.h"
#include "../../components/transform.h"
#include "riderMove.h"
#include <iostream>
#include <string>

Rider::Rider(Scene* scene, Transform* parent, RiderType riderType)
    : GameObject(scene, parent, new RiderMove(this), GameObjectRenderType::Mesh3D, RenderFileSelection(riderType))
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
}

Rider::~Rider()
{
}

std::string Rider::RenderFileSelection(RiderType riderType)
{
    std::string renderFile;
    switch (riderType) {
    case RiderType::BaseHuman:
        renderFile = "../assets/models/BaseHuman.obj";
        break;
    default:
        std::cout << "RiderType error" << std::endl;
        break;
    }
    return renderFile;
}