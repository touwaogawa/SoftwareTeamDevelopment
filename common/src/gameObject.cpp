#include "gameObject.h"
#include "component.h"
#include "component/behaviour.h"
#include "component/rigidBody.h"
#include "component/transform.h"
#include "scene.h"
#include "sceneManager.h"
#include <algorithm>

GameObject::GameObject(const std::string& name, const std::string& tag, bool isActive)
    : mTransform(new Transform(this))
    , mBehaviour(nullptr)
    , mIsActive(isActive)
    , mName(name)
    , mTag(tag)
{
    AddComponent(mTransform);
    // std::cout << "scene: " << SceneManager::GetCurrentScene() << std::endl;
    SceneManager::GetCurrentScene()->AddGameObject(this);
}

GameObject::~GameObject()
{
    // コンポーネントをすべて削除
    for (Component* component : mComponents) {
        delete component;
    }
    mComponents.clear();
}

void GameObject::SetIsActive(bool isActive)
{
    if (mIsActive != isActive) {
        mIsActive = isActive;
        UpdateChildrenActive(isActive);
    }
}

void GameObject::SetBehaviour(Behaviour* behaviour)
{
    if (mBehaviour) {
        RemoveComponent(mBehaviour);
        delete mBehaviour;
    }
    mBehaviour = behaviour;
    if (mBehaviour) {
        AddComponent(mBehaviour);
        mBehaviour->Awake();
        if (mIsActive && mBehaviour->GetEnabled()) {
            mBehaviour->OnEnable();
        }
    }
}

void GameObject::AddComponent(class Component* component)
{
    mComponents.push_back(component);
    component->Init();
}

void GameObject::RemoveComponent(Component* component)
{
    auto end = std::remove(mComponents.begin(), mComponents.end(), component);
    mComponents.erase(end, mComponents.end());
}

void GameObject::Destroy()
{
    for (Transform* child : mTransform->GetChildren()) {
        child->GetLocalPosition();
        child->GetOwner()->Destroy();
    }
    SceneManager::GetCurrentScene()->AddDestroyOject(this);
    SceneManager::GetCurrentScene()->RemoveGameObject(this);

    if (mTransform->GetParent()) {
        mTransform->SetParent(nullptr);
    }

    if (mBehaviour) {
        mBehaviour->OnDisable();
    }
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

void GameObject::UpdateChildrenActive(bool isActive)
{
    if (mIsActive) {
        if (isActive) {
            Enable();
        } else {
            Disable();
        }
    }
    for (Transform* child : mTransform->GetChildren()) {
        child->GetOwner()->UpdateChildrenActive(isActive);
    }
}