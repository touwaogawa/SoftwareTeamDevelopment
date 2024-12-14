#pragma once

class Component {
public:
    explicit Component(class GameObject* owner);
    virtual ~Component() = 0;
    class GameObject* GetOwner();

protected:
    class GameObject* mOwner;
};