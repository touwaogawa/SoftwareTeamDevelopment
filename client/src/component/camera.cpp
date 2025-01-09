#include "camera.h"
#include "../renderer.h"
Camera::Camera(GameObject* owner, const std::string& cameraName, const Matrix4& projection)
    : Component(owner)
    , mCameraName(cameraName)
    , mProjection(projection)
{
    Renderer::AddCamera(mCameraName, this);
}
Camera::~Camera()
{
    Renderer::RemoveCamera(mCameraName);
}