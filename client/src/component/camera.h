#pragma once
#include "../../../common/src/component.h"
#include "../../../utils/src/math.h"
#include <string>
class GameObject;
class Camera : public Component {
public:
    Camera(GameObject* owner, const Matrix4& projection);
    ~Camera() override;
    void Use();
    void SetProjection(Matrix4 projection) { mProjection = projection; }

private:
    void Enable() override {};
    void Disable() override;
    Matrix4 mProjection;
};