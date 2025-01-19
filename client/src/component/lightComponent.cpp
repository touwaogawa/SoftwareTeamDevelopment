#include "lightComponent.h"
#include "../../../common/src/component/transform.h"
#include "../renderer.h"

LightComponent::LightComponent(GameObject* owner, const Matrix4& projection, bool useTarget)
    : Component(owner)
    , mProjection(projection)
    , mColor(Vector3(1.0f, 1.0f, 1.0f))
    , mUseTarget(useTarget)
    , mTarget(Vector3(0.0f, 0.0f, 0.0f))
    , mUp(Vector3(0.0f, 1.0f, 0.0f))
{
}

LightComponent::~LightComponent()
{
    if (this == Renderer::GetLightComponent()) {
        Renderer::SetLightComponent(nullptr);
    }
}

void LightComponent::Use()
{
    Renderer::SetLightComponent(this);
}

const Matrix4 LightComponent::GetView()
{
    if (mUseTarget) {
        // std::cout << "mUseTarget" << std::endl;
        GetTransform()->GetWorldPosition();
        // std::cout << "mUseTarget" << std::endl;
        return Matrix4::CreateLookAt(GetTransform()->GetWorldPosition(), mTarget, mUp);
        // std::cout << "mUseTarget" << std::endl;
    } else {
        // std::cout << "!mUseTarget" << std::endl;
        return GetTransform()->GetWorldMatrix();
    }
}

void LightComponent::Disable()
{
    if (this == Renderer::GetLightComponent()) {
        Renderer::SetLightComponent(nullptr);
    }
}