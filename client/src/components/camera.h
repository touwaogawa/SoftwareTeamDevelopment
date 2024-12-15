#pragma once
#include "../component.h"
#include "../math.h"
class Camera : public Component {
public:
private:
    Matrix4 mView;
};