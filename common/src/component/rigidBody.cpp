#include "rigidBody.h"
#include "../../../utils/src/math.h"
#include "../gameObject.h"
#include "../physics.h"
#include "transform.h"

// #include <reactphysics3d/reactphysics3d.h>

RigidBody::RigidBody(GameObject* owner, rp3d::BodyType bodyType, Physics* physics)
    : Component(owner)
    , mPhysics(physics)
{
    rp3d::Vector3 rp3d_pos;
    rp3d::Quaternion rp3d_q;
    rp3d::Transform t(rp3d_pos, rp3d_q);
    mRigidBody = mPhysics->GetPhysicsWorld()->createRigidBody(t);
    mRigidBody->setType(bodyType);
    mPhysics->AddRigidBody(this);
    mRigidBody->setUserData(static_cast<void*>(mOwner));
    SetTransform();
}

RigidBody::~RigidBody()
{
    mPhysics->GetPhysicsWorld()->destroyRigidBody(mRigidBody);
    mPhysics->RemoveRigidBody(this);
}

void RigidBody::SetTransform()
{
    Transform* transform = mOwner->GetTransform();
    Vector3 pos          = transform->GetWorldPosition();
    Quaternion q         = transform->GetWorldRotation();
    rp3d::Vector3 rp3d_pos(pos.x, pos.y, pos.z);
    rp3d::Quaternion rp3d_q(q.x, q.y, q.z, q.w);
    rp3d::Transform t(rp3d_pos, rp3d_q);
    mRigidBody->setTransform(t);
}

void RigidBody::UpdateTransform()
{
    rp3d::Transform t  = mRigidBody->getTransform();
    rp3d::Vector3 pos  = t.getPosition();
    rp3d::Quaternion q = t.getOrientation();
    // std::cout << "x: " << pos.x
    //           << "y: " << pos.y
    //           << "z: " << pos.z
    //           << std::endl;
    mOwner->GetTransform()->SetWorldPosition(static_cast<float>(pos.x), static_cast<float>(pos.y), static_cast<float>(pos.z));
    mOwner->GetTransform()->SetWorldRotation(Quaternion(static_cast<float>(q.x), static_cast<float>(q.y), static_cast<float>(q.z), static_cast<float>(q.w)));
}