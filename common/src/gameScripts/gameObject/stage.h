#pragma once
#include "../../../../common/src/gameObject.h"
#include "../../../../utils/src/math.h"
#include <string>

class Physics;
class Stage : public GameObject {
public:
    Stage(Physics* physics, const std::string& meshFileName);
    virtual ~Stage() override = default;

private:
    std::vector<Vector3> LoadObjFile(const std::string& fileName);
};