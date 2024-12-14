#include "gameObject.h"
#include "component.h"
#include "components/behaviour.h"
#include "components/transform.h"
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
}

GameObject::~GameObject()
{
    for (Transform* child : mTransform->GetChildren()) {

        child->GetOwner()->~GameObject();
    }
    for (Component* component : mComponents) {
        delete component;
    }
}

Behaviour* GameObject::GetBehaviour() const
{
    return mBehaviour;
}

Scene* GameObject::GetScene() const
{
    return mScene;
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