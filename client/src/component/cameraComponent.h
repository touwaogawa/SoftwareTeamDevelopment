#pragma once
#include "../../../common/src/component.h"
#include "../../../utils/src/math.h"
#include <string>
class GameObject;
class CameraComponent : public Component {
public:
    CameraComponent(GameObject* owner, const Matrix4& projection, bool useTarget = true);
    ~CameraComponent() override;
    void Use();

    void SetProjection(Matrix4 projection) { mProjection = projection; }
    const Matrix4 GetProjection() const { return mProjection; }

    void SetTarget(const Vector3& target) { mTarget = target; }
    void SetUp(const Vector3& up) { mUp = up; }
    void SetUseTarget(bool useTarget) { mUseTarget = useTarget; }

    const Matrix4 GetView();

private:
    void Enable() override {};
    void Disable() override;
    Matrix4 mProjection;
    bool mUseTarget;
    Vector3 mTarget;
    Vector3 mUp;
};