#pragma once
#include "../../../common/src/component.h"
#include "../../../utils/src/math.h"
#include <string>
class GameObject;
class Camera : public Component {
public:
    Camera(GameObject* owner, const std::string& cameraName, const Matrix4& projection);
    ~Camera();
    void Use();
    const std::string& GetCameraName() const { return mCameraName; }
    void SetProjection(Matrix4 projection) { mProjection = projection; }

private:
    const std::string mCameraName;
    Matrix4 mProjection;
};