#pragma once
#include "../../../../common/src/gameObject.h"
#include <string>

enum class BeyType {
    Shuriken,
    BeyTypeNum
};
class Bey : public GameObject {
public:
    Bey(class Scene* scene, class Transform* parent, BeyType beyType);
    ~Bey() override;

private:
    std::string RenderFileSelection(BeyType beyType);
};