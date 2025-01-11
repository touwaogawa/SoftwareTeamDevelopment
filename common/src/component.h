#pragma once

class GameObject;
class Component {
public:
    explicit Component(GameObject* owner)
        : mOwner(owner)
    {
    }
    virtual ~Component();
    GameObject* GetOwner() { return mOwner; }

protected:
    GameObject* mOwner;
};