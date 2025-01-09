#pragma once
class Component {
public:
    explicit Component(class GameObject* owner)
        : mOwner(owner)
    {
    }
    virtual ~Component() = default;
    class GameObject* GetOwner() { return mOwner; }

protected:
    class GameObject* mOwner;
};