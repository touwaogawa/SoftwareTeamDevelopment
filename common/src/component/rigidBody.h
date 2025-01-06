#pragma once
#include "../component.h"
#include <reactphysics3d/reactphysics3d.h>

class RigidBody : public Component {
public:
    RigidBody(class GameObject* owner, rp3d::BodyType bodyType, class Physics* physics);
    ~RigidBody();
    rp3d::RigidBody* mRigidBody;
    void SetTransform();
    void UpdateTransform();
    void SetVA(float x, float y, float z);

private:
    rp3d::Transform mTransform;
    class Physics* mPhysics;
};