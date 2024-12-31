#pragma once
#include "../../../../common/src/gameObject.h"
#include <string>

enum class RiderType {
    BaseHuman,
    RiderTypeNum
};
class Rider : public GameObject {
public:
    Rider(Scene* scene, Transform* parent, RiderType riderType);
    ~Rider() override;

private:
    std::string RenderFileSelection(RiderType riderType);
};