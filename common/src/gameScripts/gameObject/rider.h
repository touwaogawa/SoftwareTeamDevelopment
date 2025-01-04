#pragma once
#include "../../../../common/src/gameObject.h"

enum class RiderType {
    BaseHuman,
    RiderTypeNum
};

struct RiderBaseStatus {
    float mass = 50.0f; // 質量
};
class Rider : public GameObject {
public:
    Rider(Scene* scene, Transform* parent, RiderType riderType, class RiderMove* riderMove);
    ~Rider() override;

protected:
private:
    RiderBaseStatus mRiderBaseStatus;
};