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

void GameObject::RemoveComponent(Component* component)
{
    auto end = std::remove(mComponents.begin(), mComponents.end(), component);
    mComponents.erase(end, mComponents.end());
}