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

private:
    rp3d::Transform mTransform;
    class Physics* mPhysics;
};