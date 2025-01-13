#pragma once
#include "../../utils/src/math.h"
#include <string>
#include <vector>
class GameObject;
class Transform;
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
    virtual void Start() {};

    /// @brief Call the Update method and LateUpdate method of all gameobject and update physics
    /// @param exitFrag
    /// @param timeStep //seccond
    virtual void Update(bool& exitFrag, float timeStep_sec);

    void Instantiate(GameObject* original, Transform* parent = nullptr, bool instantiateInWorldSpace = true);
    void Instantiate(GameObject* original, Matrix4 transform, Transform* parent = nullptr);

    void AddRootObject(GameObject* gameObject);
    void RemoveRootObject(GameObject* gameObject);

    class Physics* GetPhysics() { return mPhysics; }

    std::string GetName() const;
    int currentFrame;

    void AddDestroyOject(GameObject* gameObject) { mDestroyObjects.push_back(gameObject); }

protected:
    std::string mName;
    std::vector<GameObject*> mRootObjects;
    std::vector<GameObject*> mDestroyObjects;
    class Physics* mPhysics;

    void DeteleAllObject();

private:
    void StartgameScriptsFromRoot(GameObject* rootObject);
    void UpdategameScriptsFromRoot(GameObject* rootObject);
    void LateUpdategameScriptsFromRoot(GameObject* rootObject);

    void DeleteFromRootObject(GameObject* rootObject);
};