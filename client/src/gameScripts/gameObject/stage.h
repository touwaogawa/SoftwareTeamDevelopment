#pragma once
#include "../../../../common/src/gameScripts/gameObject/stage.h"
#include <string>
class Physics;
class Stage_C : public Stage {
public:
    Stage_C(Physics* physics,
        const std::string& meshFileName  = "../assets/models/Stage.obj",
        const std::string& imageFileName = "../assets/textures/simpleTile.png", bool isConvex = true);
    ~Stage_C() override = default;
};