#pragma once
#include <string>
#include <vector>

class Scene;
class Transform;
class Behaviour;
class Component;

class GameObject {
public:
    /// @brief constructor of the class GameObject
    /// @param name
    /// @param tag
    /// @param isActive
    GameObject(const std::string& name = "GameObject", const std::string& tag = "Default", bool isActive = true);

    /// Destructor
    virtual ~GameObject();

    bool GetIsActive() const { return mIsActive; }
    void SetIsActive(bool isActive);

    /// @brief
    // virtual void Init() = 0;

    /// @brief return the Scene in which this class exists
    /// @return
    /// @brief return the Transform Component attached to this GameObject
    Transform* const GetTransform() const { return mTransform; }

    /// @brief Return the Behaviour Component attached to this GameObject
    Behaviour* const GetBehaviour() const { return mBehaviour; }

    void SetBehaviour(Behaviour* behaviour);

    /// @brief Return a specified type of component
    /// @tparam T
    /// @return Returns the specified component if it exists; otherwise, returns nullptr
    template <typename T>
    T* const GetComponent()
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

    const std::string& GetName() const { return mName; }
    const std::string& GetTag() const { return mTag; }

protected:
    std::vector<Component*> mComponents;
    Transform* const mTransform;
    Behaviour* mBehaviour;
    bool mIsActive;

private:
    const std::string mName;
    const std::string mTag;

    static std::vector<GameObject*> mGameObjects;
    static std::vector<GameObject*> mDestroyObjects;

    void Enable();
    void Disable();
    void UpdateChildrenActive(bool isActive);
};