#pragma once
#include "../../../../common/src/gameObject.h"

class RiderMove;
enum class RiderType {
    BaseHuman,
    RiderTypeNum
};

struct RiderBaseStatus {
    float mass = 50.0f; // 質量
};
class Rider : public GameObject {
public:
    explicit Rider(RiderType riderType);
    ~Rider() override;

protected:
private:
    RiderBaseStatus mRiderBaseStatus;
};