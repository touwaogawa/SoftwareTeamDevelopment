#pragma once
#include "../../../../../common/src/gameObject.h"
#include "../../../../../utils/src/math.h"
#include <string>

class SimpleSprite : public GameObject {
public:
    SimpleSprite(Scene* scene, Transform* parent, const Matrix4& initialTransform, const std::string& fileName);
    ~SimpleSprite();

private:
};