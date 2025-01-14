#pragma once
#include "../component.h"
#include <reactphysics3d/reactphysics3d.h>

class RigidBody : public Component {
public:
    /// @brief Constructor
    /// @param owner
    /// @param bodyType
    /// @param physics
    RigidBody(class GameObject* owner, rp3d::BodyType bodyType, class Physics* physics);

    /// @brief Destructor
    ~RigidBody() override;

    void SetIsActive(bool isActive) { mRigidBody->setIsActive(isActive); }
    bool GetIsActive() { return mRigidBody->isActive(); }

    /// @brief Return rp3d::RigidBody
    /// @return The pointer of rp3d::RigidBody
    rp3d::RigidBody* GetRp3dRogidBody() const { return mRigidBody; }

    void SetTransform();
    void UpdateTransform();

private:
    void Enable() override { mRigidBody->setIsActive(true); }
    void Disable() override { mRigidBody->setIsActive(false); }

    rp3d::RigidBody* mRigidBody;
    class Physics* mPhysics;
};