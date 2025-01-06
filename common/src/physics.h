#pragma once
// #include "component/rigidBody.h"
#include <reactphysics3d/reactphysics3d.h>
#include <vector>
class MyEventListener : public rp3d::EventListener {
public:
    // onCollision をオーバーライド
    void onContact(const rp3d::CollisionCallback::CallbackData& callbaclData) override;
    void onTrigger(const rp3d::OverlapCallback::CallbackData& callbackData) override;
};

class Physics {
public:
    Physics();
    ~Physics();
    void Update(float timeStep);
    reactphysics3d::PhysicsWorld* GetPhysicsWorld() const;
    void AddRigidBody(class RigidBody* rigidBody)
    {
        mRigidBodies.push_back(rigidBody);
    }
    void RemoveRigidBody(class RigidBody* rigidBody);

    static reactphysics3d::PhysicsCommon mPhysicsCommon;
    reactphysics3d::PhysicsWorld* mPhysicsWorld;
    MyEventListener* mMyEventListener;

    std::vector<class RigidBody*> mRigidBodies;
};
