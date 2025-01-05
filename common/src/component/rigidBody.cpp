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
    Transform* transform = mOwner->GetTransform();
    SetTransform();
    mRigidBody = mPhysics->GetPhysicsWorld()->createRigidBody(mTransform);
    mRigidBody->setType(bodyType);
    mPhysics->AddRigidBody(this);
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
    mTransform = rp3d::Transform(rp3d_pos, rp3d_q);
}

void RigidBody::UpdateTransform()
{
    rp3d::Vector3 pos  = mTransform.getPosition();
    rp3d::Quaternion q = mTransform.getOrientation();
    mOwner->GetTransform()->SetWorldPosition(Vector3(pos.x, pos.y, pos.z));
    mOwner->GetTransform()->SetWorldRotation(Quaternion(q.x, q.y, q.z, q.w));
}