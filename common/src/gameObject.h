#pragma once
#include <vector>

class Scene;
class Transform;
class Behaviour;
class Component;

class GameObject {
public:
    /// @brief constructor of the class GameObject
    /// @param scene
    /// @param parent
    /// @param behaviour
    explicit GameObject(bool isActive = true);

    /// Destructor
    virtual ~GameObject();

    bool GetIsActive() const { return mIsActive; }
    void SetIsActive(bool isActive);

    /// @brief
    // virtual void Init() = 0;

    /// @brief return the Scene in which this class exists
    /// @return
    Scene* GetScene() const { return mScene; }
    void SetScene(Scene* owner) { mScene = owner; }
    /// @brief return the Transform Component attached to this GameObject
    Transform* GetTransform() const { return mTransform; }

    /// @brief Return the Behaviour Component attached to this GameObject
    Behaviour* GetBehaviour() const { return mBehaviour; }

    void SetBehaviour(Behaviour* behaviour);

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
    void AddComponent(Component* component);
    /// @brief Remove the specified and erase the component from the conponent list of this GameObject
    /// @param component
    void RemoveComponent(Component* component);

    void Destroy();

protected:
    std::vector<Component*> mComponents;
    Transform* mTransform;
    Behaviour* mBehaviour;
    bool mIsActive;

    Scene* mScene;

private:
    void Enable();
    void Disable();
    void UpdateChildren(bool isActive);
};