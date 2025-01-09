#pragma once
#include <string>
#include <vector>
class Scene {
public:
    /// @brief Constructor
    /// @param name
    Scene(std::string name);

    /// @brief Destructor
    virtual ~Scene();

    /// @brief Scene load
    /// @return Return false, if failed to load
    virtual bool Load() = 0;

    /// @brief Call the Start methos of all gameobject
    virtual void Start();

    /// @brief Call the Update method and LateUpdate method of all gameobject and update physics
    /// @param exitFrag
    /// @param timeStep //seccond
    virtual void Update(bool& exitFrag, float timeStep_sec);

    void AddGameObject(class GameObject* gameObject);
    void RemoveGameObject(class GameObject* gameObject);

    void AddRootObject(class GameObject* gameObject);
    void RemoveRootObject(class GameObject* gameObject);

    class Physics* GetPhysics() { return mPhysics; }

    std::string GetName() const;
    int currentFrame;

protected:
    std::string mName;
    std::vector<class GameObject*> mRootObjects;
    std::vector<class GameObject*> mGameObjects;
    class Physics* mPhysics;

    void DeteleAllObject();

private:
    void StartgameScriptsFromRoot(class GameObject* rootObject);
    void UpdategameScriptsFromRoot(class GameObject* rootObject);
    void LateUpdategameScriptsFromRoot(class GameObject* rootObject);
};