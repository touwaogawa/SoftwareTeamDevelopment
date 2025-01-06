#pragma once
#include <vector>

class GameObject {
public:
    GameObject(class Scene* owner, class Transform* parent, class Behaviour* behaviour = nullptr);
    virtual ~GameObject();

    class Scene* GetScene() const;
    class Transform* GetTransform() const;
    class Behaviour* GetBehaviour() const;

    template <typename T>
    T* GetComponent()
    {
        for (Component* comp : mComponents) {
            T* casted = dynamic_cast<T*>(comp);
            if (casted) {
                return casted;
            }
        }
        return nullptr;
    }

    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);

protected:
    class Scene* mScene;
    class Transform* mTransform;
    class Behaviour* mBehaviour;
    std::vector<class Component*> mComponents;
};