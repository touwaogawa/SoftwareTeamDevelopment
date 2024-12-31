#pragma once
#include <string>
#include <vector>
enum class GameObjectRenderType {
    NON_Render,
    Mesh3D,
    Sprite,
    GameObjectRenderTypeNum

};
class GameObject {
public:
    GameObject(class Scene* owner, class Transform* parent, class Behaviour* behaviour, GameObjectRenderType gameObjectRenderType = GameObjectRenderType::NON_Render, std::string renderFile = std::string());
    virtual ~GameObject();

    class Scene* GetScene() const;
    class Transform* GetTransform() const;
    class Behaviour* GetBehaviour() const;

    template <typename T>
    T* GetComponent();

    void AddComponent(class Component* component);
    void RemoveComponent(class Component* component);

    GameObjectRenderType GetRenderType() const;
    std::string GetRenderFile() const;

protected:
    class Scene* mScene;
    class Transform* mTransform;
    class Behaviour* mBehaviour;
    std::vector<class Component*> mComponents;

    GameObjectRenderType mGameObjectRenderType;
    std::string mRenderFile;
};