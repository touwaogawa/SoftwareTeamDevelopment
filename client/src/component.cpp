#include "component.h"
#include "gameObject.h"

Component::Component(GameObject* owner)
    : mOwner(owner)
    , mTransform(mOwner->GetTransform())
{
}
Component::~Component()
{
}
GameObject* Component::GetOwner()
{
    return mOwner;
}