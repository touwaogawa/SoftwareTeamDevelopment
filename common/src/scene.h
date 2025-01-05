#pragma once
#include <string>
#include <vector>
class Scene {
public:
    Scene(std::string name);
    virtual ~Scene();
    virtual bool Load() = 0;

    virtual void Start();
    virtual void Update(bool& exitFrag, float timeStep);

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
    std::vector<class GameObject*> mgameObjects;

    void RemoveAllObject();

private:
    class Physics* mPhysics;
    void StartgameScriptsFromRoot(class GameObject* rootObject);
    void UpdategameScriptsFromRoot(class GameObject* rootObject);
    void LateUpdategameScriptsFromRoot(class GameObject* rootObject);
};