#include "lightComponent.h"
#include "../renderer.h"
LightComponent::LightComponent(GameObject* owner, const Matrix4& projection)
    : Component(owner)
    , mProjection(projection)
    , mColor(Vector3(1.0f, 1.0f, 1.0f))
{
}

void LightComponent::Use()
{
    Renderer::SetLightComponent(this);
}
LightComponent::~LightComponent()
{
    if (this == Renderer::GetLightComponent()) {
        Renderer::SetLightComponent(nullptr);
    }
}

void LightComponent::Disable()
{
    if (this == Renderer::GetLightComponent()) {
        Renderer::SetLightComponent(nullptr);
    }
}