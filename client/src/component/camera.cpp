#include "camera.h"
#include "../renderer.h"
Camera::Camera(GameObject* owner, const std::string& cameraName, const Matrix4& projection)
    : Component(owner)
    , mCameraName(cameraName)
    , mProjection(projection)
{
    Renderer::AddCamera(mCameraName, this);
}

void Camera::Use()
{
    Renderer::UseCamera(mCameraName);
}
Camera::~Camera()
{
    Renderer::RemoveCamera(mCameraName);
}