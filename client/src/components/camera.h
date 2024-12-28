#pragma once
#include "../../../common/src/component.h"
#include "../../../utils/src/math.h"
class Camera : public Component {
public:
private:
    Matrix4 mView;
};