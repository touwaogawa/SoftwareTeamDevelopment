#pragma once
#include "../../../common/src/component.h"
#include "../../../utils/src/math.h"
#include <string>
class GameObject;
class LightComponent : public Component {
public:
    LightComponent(GameObject* owner, const Matrix4& projection, bool useTarget = true);
    ~LightComponent() override;
    void Use();

    void SetProjection(Matrix4 projection) { mProjection = projection; }
    const Matrix4& GetProjection() const { return mProjection; }

    void SetColor(Vector3 color) { mColor = color; }
    const Vector3& GetColor() const { return mColor; }

    void SetTarget(const Vector3& target) { mTarget = target; }
    void SetUp(const Vector3& up) { mUp = up; }
    void SetUseTarget(bool useTarget) { mUseTarget = useTarget; }

    const Matrix4 GetView();

private:
    void Enable() override {};
    void Disable() override;
    Matrix4 mProjection;
    Vector3 mColor;
    bool mUseTarget;
    Vector3 mTarget;
    Vector3 mUp;
};