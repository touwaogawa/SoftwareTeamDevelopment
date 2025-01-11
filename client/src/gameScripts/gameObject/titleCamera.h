#pragma once
#include "../../../../common/src/gameObject.h"

class TitleCamera : public GameObject {
public:
    TitleCamera(Scene* scene, Transform* parent);
    ~TitleCamera() override = default;
};