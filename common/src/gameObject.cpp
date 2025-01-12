#include "gameObject.h"
#include "component.h"
#include "component/behaviour.h"
#include "component/rigidBody.h"
#include "component/transform.h"
#include "scene.h"
#include <algorithm>

GameObject::GameObject(bool isActive)
    : mTransform(new Transform(this))
    , mBehaviour(nullptr)
    , mIsActive(isActive)
{
    AddComponent(mTransform);
}

GameObject::~GameObject()
{
    // コンポーネントをすべて削除
    for (Component* component : mComponents) {
        delete component;
    }
}

void GameObject::SetIsActive(bool isActive)
{
    if (mIsActive != isActive) {
        mIsActive = isActive;
        UpdateChildren(isActive);
    }
}

void GameObject::SetBehaviour(Behaviour* behaviour)
{
    if (mBehaviour) {
        RemoveComponent(mBehaviour);
    }
    mBehaviour = behaviour;
    if (mBehaviour) {
        AddComponent(mBehaviour);
    }
}

void GameObject::AddComponent(class Component* component)
{
    mComponents.push_back(component);
    component->SetTransform(mTransform);
}

void GameObject::RemoveComponent(Component* component)
{
    auto end = std::remove(mComponents.begin(), mComponents.end(), component);
    mComponents.erase(end, mComponents.end());
}

void GameObject::Destroy()
{
    mScene->AddDestroyOject(this);
}

void GameObject::Enable()
{
    for (Component* component : mComponents) {
        component->Enable();
    }
}

void GameObject::Disable()
{
    for (Component* component : mComponents) {
        component->Disable();
    }
}

void GameObject::UpdateChildren(bool isActive)
{
    if (mIsActive) {
        if (isActive) {
            Enable();
        } else {
            Disable();
        }
    }
    for (Transform* child : mTransform->GetChildren()) {
        child->GetOwner()->UpdateChildren(isActive);
    }
}