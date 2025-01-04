#pragma once
#include "../../../../common/src/gameObject.h"

class Stage : public GameObject {
public:
    Stage(Scene* scene, Transform* parent);
    ~Stage() override;

private:
};