#pragma once
#include "../../../common/src/component.h"
#include "../../../utils/src/math.h"
#include <string>
class GameObject;
class LightComponent : public Component {
public:
    LightComponent(GameObject* owner, const Matrix4& projection);
    ~LightComponent() override;
    void Use();

    void SetProjection(Matrix4 projection) { mProjection = projection; }
    const Matrix4& GetProjection() const { return mProjection; }

    void SetColor(Vector3 color) { mColor = color; }
    const Vector3& GetColor() const { return mColor; }

private:
    void Enable() override {};
    void Disable() override;
    Matrix4 mProjection;
    Vector3 mColor;
};