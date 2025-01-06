#include "gameObject.h"
#include "component.h"
#include "component/behaviour.h"
#include "component/transform.h"
#include "scene.h"
#include <algorithm>

GameObject::GameObject(Scene* scene, Transform* parent, Behaviour* behaviour)
    : mScene(scene)
    , mTransform(new Transform(this, parent))
    , mBehaviour(behaviour)
{
    AddComponent(mTransform);
    if (mTransform->GetParent() == nullptr) {
        mScene->AddRootObject(this);
    }
    mScene->AddGameObject(this);
    if (mBehaviour != nullptr) {
        AddComponent(mBehaviour);
    }
}

GameObject::~GameObject()
{
    // 子オブジェクトをすべて削除
    for (Transform* child : mTransform->GetChildren()) {

        child->GetOwner()->~GameObject();
    }
    // コンポーネントをすべて削除
    for (Component* component : mComponents) {
        delete component;
    }
}

Scene* GameObject::GetScene() const
{
    return mScene;
}

Transform* GameObject::GetTransform() const
{
    return mTransform;
}

Behaviour* GameObject::GetBehaviour() const
{
    return mBehaviour;
}

void GameObject::AddComponent(Component* component)
{
    mComponents.push_back(component);
}

void GameObject::RemoveComponent(Component* component)
{
    auto end = std::remove(mComponents.begin(), mComponents.end(), component);
    mComponents.erase(end, mComponents.end());
}