#include "component.h"
#include "gameObject.h"

Component::Component(GameObject* owner)
    : mOwner(owner)
{
}

GameObject* Component::GetOwner()
{
    return mOwner;
}