#include "physics.h"
#include "component/collider.h"
#include "component/rigidBody.h"
reactphysics3d::PhysicsCommon Physics::mPhysicsCommon;

Physics::Physics()
    : mPhysicsWorld(mPhysicsCommon.createPhysicsWorld())
{
    mMyEventListener = new MyEventListener();
    mPhysicsWorld->setEventListener(mMyEventListener);
}
Physics::~Physics()
{
    delete mMyEventListener;
    mPhysicsCommon.destroyPhysicsWorld(mPhysicsWorld);
}
reactphysics3d::PhysicsWorld* Physics::GetPhysicsWorld() const
{
    return mPhysicsWorld;
}

void Physics::Update(float timeStep /*経過時間*/)
{
    // Transform -> rp3d::Transform
    for (RigidBody* rigidBody : mRigidBodies) {
        rigidBody->SetTransform();
    }
    // 物理演算
    mPhysicsWorld->update(static_cast<rp3d::decimal>(timeStep));
    // rp3d::Transfrom ->Transform
    for (RigidBody* rigidBody : mRigidBodies) {
        rigidBody->UpdateTransform();
    }
}

void Physics::RemoveRigidBody(RigidBody* rigidBody)
{
    auto end = std::remove(mRigidBodies.begin(), mRigidBodies.end(), rigidBody);
    mRigidBodies.erase(end, mRigidBodies.end());
}

void MyEventListener::onContact(const CallbackData& callbackData)
{
    int numPairs = callbackData.getNbContactPairs();
    for (int i = 0; i < numPairs; i++) {
        const rp3d::CollisionCallback::ContactPair pair = callbackData.getContactPair(i);
        const rp3d::Collider* collider1                 = pair.getCollider1();
        const rp3d::Collider* collider2                 = pair.getCollider2();
        const rp3d::Body* rigidBody1                    = pair.getBody1();
        const rp3d::Body* rigidBody2                    = pair.getBody2();
        Collider* colliderComponent1                    = static_cast<Collider*>(collider1->getUserData());
        Collider* colliderComponent2                    = static_cast<Collider*>(collider2->getUserData());

        switch (pair.getEventType()) {
        case rp3d::CollisionCallback::ContactPair::EventType::ContactStart:
            colliderComponent1->OnCollisionEnter(collider1, collider2, pair);
            colliderComponent2->OnCollisionEnter(collider2, collider1, pair);
            break;
        case rp3d::CollisionCallback::ContactPair::EventType::ContactStay:
            colliderComponent1->OnCollisionStay(collider1, collider2, pair);
            colliderComponent2->OnCollisionStay(collider2, collider1, pair);
            break;
        case rp3d::CollisionCallback::ContactPair::EventType::ContactExit:
            colliderComponent1->OnCollisionExit(collider1, collider2, pair);
            colliderComponent2->OnCollisionExit(collider2, collider1, pair);
            break;
        default:
            std::cout << "rp3d::CollisionCallback::ContactPair::EventType error" << std::endl;
            break;
        }
    }
}

void MyEventListener::onTrigger(const rp3d::OverlapCallback::CallbackData& callbackData)
{

    int numPairs = callbackData.getNbOverlappingPairs();
    for (int i = 0; i < numPairs; i++) {
        const const rp3d::OverlapCallback::OverlapPair pair = callbackData.getOverlappingPair(i);
        const rp3d::Collider* collider1                     = pair.getCollider1();
        const rp3d::Collider* collider2                     = pair.getCollider2();
        const rp3d::Body* rigidBody1                        = pair.getBody1();
        const rp3d::Body* rigidBody2                        = pair.getBody2();
        Collider* colliderComponent1                        = static_cast<Collider*>(collider1->getUserData());
        Collider* colliderComponent2                        = static_cast<Collider*>(collider2->getUserData());

        switch (pair.getEventType()) {
        case rp3d::OverlapCallback::OverlapPair::EventType::OverlapStart:
            colliderComponent1->OnOverlapEnter(collider1, collider2, pair);
            colliderComponent2->OnOverlapEnter(collider2, collider1, pair);
            break;
        case rp3d::OverlapCallback::OverlapPair::EventType::OverlapStay:
            colliderComponent1->OnOverlapStay(collider1, collider2, pair);
            colliderComponent2->OnOverlapStay(collider2, collider1, pair);
            break;
        case rp3d::OverlapCallback::OverlapPair::EventType::OverlapExit:
            colliderComponent1->OnOverlapExit(collider1, collider2, pair);
            colliderComponent2->OnOverlapExit(collider2, collider1, pair);
            break;
        default:
            std::cout << "rp3d::CollisionCallback::ContactPair::EventType error" << std::endl;
            break;
        }
    }
}