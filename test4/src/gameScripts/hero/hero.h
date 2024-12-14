#pragma once

#include "../../gameObject.h"

class Helo : public GameObject {
public:
    Helo(Scene* scene, Transform* parent);
    ~Helo() override;

private:
    GameObject* mBey;
    // GameObject* mRider;
};