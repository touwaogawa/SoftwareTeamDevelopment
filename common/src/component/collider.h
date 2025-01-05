#pragma once
#include "../component.h"
#include <reactphysics3d/reactphysics3d.h>
class Collider : public Component {
public:
    Collider(class GameObject* owner,
        rp3d::PhysicsWorld* physicsWorld,
        rp3d::CollisionShape* shape,
        rp3d::RigidBody* rigidBody,
        const rp3d::Transform offset);

    virtual void OnCollisionEnter(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::CollisionCallback::ContactPair& pair) { }
    virtual void OnCollisionStay(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::CollisionCallback::ContactPair& pair) { }
    virtual void OnCollisionExit(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::CollisionCallback::ContactPair& pair) { }

    virtual void OnOverlapEnter(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::OverlapCallback::OverlapPair& pair) { }
    virtual void OnOverlapStay(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::OverlapCallback::OverlapPair& pair) { }
    virtual void OnOverlapExit(const rp3d::Collider* self, const rp3d::Collider* opponent, const rp3d::OverlapCallback::OverlapPair& pair) { }

private:
    rp3d::PhysicsWorld* mPhysicsworld;
    rp3d::RigidBody* mRigidBody;
};