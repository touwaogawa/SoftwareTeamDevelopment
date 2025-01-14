#pragma once
#include "../../../common/src/component.h"
#include "../../../utils/src/math.h"
#include <string>
class GameObject;
class CameraComponent : public Component {
public:
    CameraComponent(GameObject* owner, const Matrix4& projection);
    ~CameraComponent() override;
    void Use();
    void SetProjection(Matrix4 projection) { mProjection = projection; }
    const Matrix4& GetProjection() const { return mProjection; }

private:
    void Enable() override {};
    void Disable() override;
    Matrix4 mProjection;
};