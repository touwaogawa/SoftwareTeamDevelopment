#pragma once
#include "../../../../common/src/gameObject.h"
#include <string>

enum class RiderType {
    BaseHuman,
    RiderTypeNum
};

struct RiderBaseStatus {
    float mass = 50.0f; // 質量
};
class Rider : public GameObject {
public:
    Rider(Scene* scene, Transform* parent, RiderType riderType);
    ~Rider() override;

private:
    std::string RenderFileSelection(RiderType riderType);
    RiderBaseStatus mRiderBaseStatus;
};