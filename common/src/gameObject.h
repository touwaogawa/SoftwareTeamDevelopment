#pragma once
#include <vector>

class GameObject {
public:
    /// @brief constructor of the class GameObject
    /// @param scene
    /// @param parent
    /// @param behaviour
    GameObject(class Scene* scene, class Transform* parent, class Behaviour* behaviour = nullptr);

    /// Destructor
    virtual ~GameObject();

    /// @brief return the Scene in which this class exists
    /// @return
    class Scene* GetScene() const { return mScene; }

    /// @brief return the Transform Component attached to this GameObject
    class Transform* GetTransform() const { return mTransform; }

    /// @brief Return the Behaviour Component attached to this GameObject
    class Behaviour* GetBehaviour() const { return mBehaviour; }

    void SetBehaviour(class Behaviour* behabiour) { mBehaviour = behabiour; }

    /// @brief Return a specified type of component
    /// @tparam T
    /// @return Returns the specified component if it exists; otherwise, returns nullptr
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

    /// @brief Add the specified Component into the component list of this GameObject
    /// @param component
    void AddComponent(class Component* component) { mComponents.push_back(component); }

    /// @brief Remove the specified and erase the component from the conponent list of this GameObject
    /// @param component
    void RemoveComponent(class Component* component);

protected:
    class Scene* mScene;
    class Transform* mTransform;
    class Behaviour* mBehaviour;
    std::vector<class Component*> mComponents;
};