#pragma once

class GameObject;
class Transform;
class Component {
public:
    explicit Component(GameObject* owner)
        : mOwner(owner)
        , mTransform(nullptr)
        , mIsInitialized(false)
    {
    }
    void Init();
    virtual ~Component() = default;
    GameObject* const GetOwner() { return mOwner; }
    Transform* const GetTransform() const { return mTransform; }

    virtual void Enable()  = 0;
    virtual void Disable() = 0;

protected:
    GameObject* const mOwner;

private:
    Transform* mTransform;
    bool mIsInitialized;
};