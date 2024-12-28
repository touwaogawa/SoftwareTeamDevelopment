#pragma once
#include <string>
#include <vector>
class Scene {
public:
    Scene(std::string name);
    virtual ~Scene();
    virtual bool Load() = 0;

    virtual bool ProccessInput() = 0;
    virtual void ProccessNetowork();

    void Start();
    void Update();
    void LateUpdate();
    void Draw();
    class Renderer* GetRenderer() const;

    void AddGameObject(class GameObject* gameObject);
    void RemoveGameObject(class GameObject* gameObject);

    void AddRootObject(class GameObject* gameObject);
    void RemoveRootObject(class GameObject* gameObject);

    std::string GetName() const;

    int currentFrame;

protected:
    std::string mName;
    std::vector<class GameObject*> mRootObjects;
    std::vector<class GameObject*> mGameObjects;
    class Renderer* mRenderer;

    void RemoveAllObject();
};