#include "rider.h"
#include "../../component/meshRenderer.h"
#include "../components/behaviour/riderMove.h"
#include <iostream>

Rider_C::Rider_C(Scene* scene, Transform* parent, RiderType riderType)
    : Rider(scene, parent, riderType, new RiderMove_C(this))
{
    // std::cout << "Rider_C constructer" << std::endl;
    switch (riderType) {
    case RiderType::BaseHuman:
        AddComponent(new MeshRenderer(this, "../assets/models/BaseHuman.obj", "../assets/textures/humanColor.png"));
        break;
    default:
        std::cout << "RiderType error" << std::endl;
        break;
    }
}
