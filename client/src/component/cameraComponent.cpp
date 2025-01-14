#include "cameraComponent.h"
#include "../renderer.h"
CameraComponent::CameraComponent(GameObject* owner, const Matrix4& projection)
    : Component(owner)
    , mProjection(projection)
{
}

void CameraComponent::Use()
{
    Renderer::SetCameraComponent(this);
}
CameraComponent::~CameraComponent()
{
    if (this == Renderer::GetCameraComponent()) {
        Renderer::SetCameraComponent(nullptr);
    }
}

void CameraComponent::Disable()
{
    if (this == Renderer::GetCameraComponent()) {
        Renderer::SetCameraComponent(nullptr);
    }
}