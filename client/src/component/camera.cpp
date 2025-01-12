#include "camera.h"
#include "../renderer.h"
Camera::Camera(GameObject* owner, const Matrix4& projection)
    : Component(owner)
    , mProjection(projection)
{
}

void Camera::Use()
{
    Renderer::SetCamera(this);
}
Camera::~Camera()
{
    if (this == Renderer::GetCamera()) {
        Renderer::SetCamera(nullptr);
    }
}

void Camera::Disable()
{
    if (this == Renderer::GetCamera()) {
        Renderer::SetCamera(nullptr);
    }
}