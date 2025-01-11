#pragma once
#include "../../../../common/src/gameObject.h"
#include "../../../../utils/src/math.h"
#include <string>

class StaticModel : public GameObject {
public:
    StaticModel(Scene* scene, Transform* parent, const Matrix4& initialTransform, const std::string& objFileName, const std::string& imageFileName);
    ~StaticModel();

private:
};