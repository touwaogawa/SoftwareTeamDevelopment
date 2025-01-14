#pragma once
#include "../../../../common/src/gameObject.h"
#include "../../../../utils/src/math.h"
#include <string>

class SimpleMeshModel : public GameObject {
public:
    SimpleMeshModel(const std::string& objFileName, const std::string& imageFileName);
    ~SimpleMeshModel();

private:
};