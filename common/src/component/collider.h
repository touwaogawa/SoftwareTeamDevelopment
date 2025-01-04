#pragma once
#include "../component.h"

class Collider : public Component {
public:
protected:
    int mLayer;

private:
};

class BoxCollider : public Collider {
};