#pragma once

#include "../../gameObject.h"

class Hero : public GameObject {
public:
    Hero(Scene* scene, Transform* parent);
    ~Hero() override;

private:
    GameObject* mBey;
    GameObject* mRider;
};