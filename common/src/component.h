#pragma once
class Component {
public:
    explicit Component(class GameObject* owner);
    virtual ~Component();
    class GameObject* GetOwner();

protected:
    class GameObject* mOwner;
};