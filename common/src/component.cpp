#include "component.h"
#include "gameObject.h"

Component::Component(GameObject* owner)
    : mOwner(owner)
{
}
Component::~Component()
{
}
GameObject* Component::GetOwner()
{
    return mOwner;
}