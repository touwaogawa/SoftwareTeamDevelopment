#pragma once
class GameObject;

class Component {
public:
    explicit Component(GameObject& owner)
        : mOwner(owner)
    {
    }
    ~Component()
    {
    }

protected:
    GameObject* mOwner;
};