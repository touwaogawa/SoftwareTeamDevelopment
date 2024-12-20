#pragma once
#include <vector>

class Scene {
public:
    Scene();
    virtual ~Scene();
    virtual bool Load();

    void Start();
    virtual bool ProccessInput() = 0;
    void Update();
    void LateUpdate();
    void Draw();
    class Renderer* GetRenderer() const;

    void AddGameObject(class GameObject* gameObject);
    void RemoveGameObject(class GameObject* gameObject);

    void AddRootObject(class GameObject* gameObject);
    void RemoveRootObject(class GameObject* gameObject);

    int currentFrame;

protected:
    std::vector<class GameObject*> mRootObjects;
    std::vector<class GameObject*> mGameObjects;
    class Renderer* mRenderer;
};