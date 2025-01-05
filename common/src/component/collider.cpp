#include "collider.h"

Collider::Collider(GameObject* owner,
    rp3d::PhysicsWorld* physicsWorld,
    rp3d::CollisionShape* shape,
    rp3d::RigidBody* rigidBody,
    const rp3d::Transform offset)
    : Component(owner)
    , mPhysicsworld(physicsWorld)
    , mRigidBody(rigidBody)
{
    rp3d::Collider* collider = mRigidBody->addCollider(shape, offset);
    collider->setUserData(static_cast<GameObject*>(owner));
}