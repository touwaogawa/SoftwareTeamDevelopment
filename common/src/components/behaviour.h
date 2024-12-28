#pragma once

#include "../component.h"

class Behaviour : public Component {
public:
    explicit Behaviour(class GameObject* owner)
        : Component(owner)
    {
    }
    virtual ~Behaviour()      = default;
    virtual void Start()      = 0;
    virtual void Update()     = 0;
    virtual void LateUpdate() = 0;

private:
};