#pragma once
#include "../../../../common/src/gameObject.h"
#include <string>

class Physics;
class Stage : public GameObject {
public:
    Stage(Physics* physics, const std::string& meshFileName);
    ~Stage() override;

private:
};