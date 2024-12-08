#pragma once

class GameObject;

class Component {
public:
    explicit Component(GameObject* owner)
        : mOwner(owner)
    {
    }
    ~Component()
    {
    }

    template <typename T>
    T* GetComponent() const;
    template <typename T>
    T* GetComponents() const;

protected:
    GameObject* mOwner;
    Transform2
};