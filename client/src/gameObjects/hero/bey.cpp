#include "bey.h"
#include "../../components/meshRenderer.h"
#include "beyMove.h"
#include <iostream>
Bey_C::Bey_C(Scene* scene, Transform* parent, BeyType beyType)
    : Bey(scene, parent, beyType, new BeyMove_C(this))
{
    switch (beyType) {
    case BeyType::Shuriken:
        AddComponent(new MeshRenderer(this, "../assets/models/Shuriken.obj"));
        break;
    default:
        std::cout << "BeyType error" << std::endl;
        break;
    }
}
