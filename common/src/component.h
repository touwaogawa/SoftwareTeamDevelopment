#pragma once

class GameObject;
class Transform;
class Component {
public:
    explicit Component(GameObject* owner)
        : mOwner(owner)
        , mTransform(nullptr)
    {
    }
    virtual ~Component() = default;
    GameObject* GetOwner() { return mOwner; }
    void SetTransform(Transform* transform) { mTransform = transform; }

    virtual void Enable()  = 0;
    virtual void Disable() = 0;

protected:
    GameObject* mOwner;
    Transform* mTransform;
};