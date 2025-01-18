#include "cameraComponent.h"
#include "../../../common/src/component/transform.h"
#include "../renderer.h"
#include <iostream>

CameraComponent::CameraComponent(GameObject* owner, const Matrix4& projection, bool useTarget)
    : Component(owner)
    , mProjection(projection)
    , mUseTarget(useTarget)
    , mTarget(Vector3(0.0f, 0.0f, 0.0f))
    , mUp(Vector3(0.0f, 1.0f, 0.0f))
{
}

CameraComponent::~CameraComponent()
{
    if (this == Renderer::GetCameraComponent()) {
        Renderer::SetCameraComponent(nullptr);
    }
}

void CameraComponent::Use()
{
    Renderer::SetCameraComponent(this);
}

const Matrix4 CameraComponent::GetView()
{
    if (mUseTarget) {
        // std::cout << "mUseTarget" << std::endl;
        return Matrix4::CreateLookAt(GetTransform()->GetWorldPosition() + mOffset, mTarget, mUp);
        // std::cout << "mUseTarget" << std::endl;
    } else {
        // std::cout << "!mUseTarget" << std::endl;
        return GetTransform()->GetWorldMatrix();
    }
}

void CameraComponent::Disable()
{
    if (this == Renderer::GetCameraComponent()) {
        Renderer::SetCameraComponent(nullptr);
    }
}