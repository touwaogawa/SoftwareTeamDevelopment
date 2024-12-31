#pragma once
#include "../../../../common/src/gameObject.h"

class Stage : public GameObject {
public:
    Stage(class Scene* scene, class Transform* parent);
    ~Stage() override;

private:
};