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

/**
 * This class is responsible to physics and manage the RigidBodies
 */
class Physics {
public:
    /// @brief Constructor
    Physics();

    /// @brief Destructor
    ~Physics();

    /// @brief Update RigidBodies
    /// @param timeStep
    void Update(float timeStep);

    void SetDynamicTransform();

    /// @brief Return the phisy world
    /// @return The pointer to the reactphysics3d::PhysicsWorld of this Phisics
    reactphysics3d::PhysicsWorld* GetPhysicsWorld() const;

    /// @brief Add the specified RigidBody into the RigidBody list
    /// @param rigidBody
    void AddRigidBody(class RigidBody* rigidBody)
    {
        mRigidBodies.push_back(rigidBody);
    }

    /// @brief Remove the specified RigidBody from the RigidBody list
    /// @param rigidBody
    void RemoveRigidBody(class RigidBody* rigidBody);

    static reactphysics3d::PhysicsCommon& GetPhysicsCommon() { return mPhysicsCommon; }

private:
    static reactphysics3d::PhysicsCommon mPhysicsCommon;
    std::vector<class RigidBody*> mRigidBodies;
    MyEventListener* mMyEventListener;
    reactphysics3d::PhysicsWorld* mPhysicsWorld;
};
