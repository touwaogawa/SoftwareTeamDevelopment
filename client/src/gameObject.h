#pragma once
#include <vector>

class GameObject {
public:
    explicit GameObject(class Scene* owner, class Transform* parent, class Behaviour* behaviour);
    virtual ~GameObject();

    class Scene* GetScene() const;
    class Transform* GetTransform() const;
    class Behaviour* GetBehaviour() const;

    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);

protected:
    class Scene* mScene;
    class Transform* mTransform;
    class Behaviour* mBehaviour;
    std::vector<class Component*> mComponents;
};