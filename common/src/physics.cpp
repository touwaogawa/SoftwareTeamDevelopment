#include "physics.h"
#include "component/behaviour.h"
#include "component/rigidBody.h"
#include "gameObject.h"

reactphysics3d::PhysicsCommon Physics::mPhysicsCommon;

Physics::Physics()
{
    // Create the world settings
    rp3d::PhysicsWorld::WorldSettings settings;
    settings.defaultVelocitySolverNbIterations = 20;
    settings.defaultPositionSolverNbIterations = 20;
    settings.isSleepingEnabled                 = false;
    settings.gravity                           = rp3d::Vector3(0, -30.81, 0);

    // Create the physics world with your settings
    mPhysicsWorld    = mPhysicsCommon.createPhysicsWorld(settings);
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

void Physics::Update(float timeStep_sec)
{
    // Transform -> rp3d::Transform
    for (RigidBody* rigidBody : mRigidBodies) {
        if (rigidBody->GetOwner()->GetIsActive()) {
            if (rigidBody->GetRp3dRogidBody()->getType() == rp3d::BodyType::KINEMATIC) {
                rigidBody->SetTransform();
            }
        }
    }
    // 物理演算
    // printf("timestep_sec : %f\n", timeStep_sec);
    mPhysicsWorld->update(static_cast<rp3d::decimal>(timeStep_sec));
    // rp3d::Transfrom ->Transform
    for (RigidBody* rigidBody : mRigidBodies) {
        if (rigidBody->GetOwner()->GetIsActive()) {
            if (rigidBody->GetRp3dRogidBody()->getType() == rp3d::BodyType::DYNAMIC) {
                rigidBody->UpdateTransform();
            }
        }
    }
}

void Physics::SetDynamicTransform()
{
    for (RigidBody* rigidBody : mRigidBodies) {
        if (rigidBody->GetRp3dRogidBody()->getType() == rp3d::BodyType::DYNAMIC) {
            rigidBody->SetTransform();
        }
    }
}

void Physics::RemoveRigidBody(RigidBody* rigidBody)
{
    auto end = std::remove(mRigidBodies.begin(), mRigidBodies.end(), rigidBody);
    mRigidBodies.erase(end, mRigidBodies.end());
}

void MyEventListener::onContact(const CallbackData& callbackData)
{
    // EventListener::onContact(callbackData);
    int numPairs = callbackData.getNbContactPairs();
    for (int i = 0; i < numPairs; i++) {
        const rp3d::CollisionCallback::ContactPair pair = callbackData.getContactPair(i);
        const rp3d::Body* body1                         = pair.getBody1();
        const rp3d::Body* body2                         = pair.getBody2();
        const rp3d::Collider* collider1                 = pair.getCollider1();
        const rp3d::Collider* collider2                 = pair.getCollider2();
        GameObject* gameObject1                         = static_cast<GameObject*>(body1->getUserData());
        GameObject* gameObject2                         = static_cast<GameObject*>(body2->getUserData());

        Behaviour* bhv1 = gameObject1->GetBehaviour();
        Behaviour* bhv2 = gameObject2->GetBehaviour();

        switch (pair.getEventType()) {
        case rp3d::CollisionCallback::ContactPair::EventType::ContactStart:
            if (bhv1) {
                if (bhv1->GetIsActiveAndEnabled()) {
                    bhv1->OnCollisionEnter(collider1, collider2, pair);
                }
            }
            if (bhv2) {
                if (bhv2->GetIsActiveAndEnabled()) {
                    bhv2->OnCollisionEnter(collider2, collider1, pair);
                }
            }
            break;
        case rp3d::CollisionCallback::ContactPair::EventType::ContactStay:
            if (bhv1) {
                if (bhv1->GetIsActiveAndEnabled()) {
                    bhv1->OnCollisionStay(collider1, collider2, pair);
                }
            }
            if (bhv2) {
                if (bhv2->GetIsActiveAndEnabled()) {
                    bhv2->OnCollisionStay(collider2, collider1, pair);
                }
            }
            break;
        case rp3d::CollisionCallback::ContactPair::EventType::ContactExit:
            if (bhv1) {
                if (bhv1->GetIsActiveAndEnabled()) {
                    bhv1->OnCollisionExit(collider1, collider2, pair);
                }
            }
            if (bhv2) {
                if (bhv2->GetIsActiveAndEnabled()) {
                    bhv2->OnCollisionExit(collider2, collider1, pair);
                }
            }
            break;
        default:
            std::cout << "rp3d::CollisionCallback::ContactPair::EventType error" << std::endl;
            break;
        }
        // std::cout << "collision" << std::endl;
    }
}

void MyEventListener::onTrigger(const rp3d::OverlapCallback::CallbackData& callbackData)
{

    int numPairs = callbackData.getNbOverlappingPairs();
    for (int i = 0; i < numPairs; i++) {
        const rp3d::OverlapCallback::OverlapPair pair = callbackData.getOverlappingPair(i);
        const rp3d::Body* body1                       = pair.getBody1();
        const rp3d::Body* body2                       = pair.getBody2();
        const rp3d::Collider* collider1               = pair.getCollider1();
        const rp3d::Collider* collider2               = pair.getCollider2();
        GameObject* gameObject1                       = static_cast<GameObject*>(body1->getUserData());
        GameObject* gameObject2                       = static_cast<GameObject*>(body2->getUserData());

        Behaviour* bhv1 = gameObject1->GetBehaviour();
        Behaviour* bhv2 = gameObject2->GetBehaviour();

        switch (pair.getEventType()) {
        case rp3d::OverlapCallback::OverlapPair::EventType::OverlapStart:
            if (bhv1) {
                if (bhv1->GetIsActiveAndEnabled()) {
                    bhv1->OnOverlapEnter(collider1, collider2, pair);
                }
            }
            if (bhv2) {
                if (bhv2->GetIsActiveAndEnabled()) {
                    bhv2->OnOverlapEnter(collider2, collider1, pair);
                }
            }
            break;
        case rp3d::OverlapCallback::OverlapPair::EventType::OverlapStay:
            if (bhv1) {
                if (bhv1->GetIsActiveAndEnabled()) {
                    bhv1->OnOverlapStay(collider1, collider2, pair);
                }
            }
            if (bhv2) {
                if (bhv2->GetIsActiveAndEnabled()) {
                    bhv2->OnOverlapStay(collider2, collider1, pair);
                }
            }
            break;
        case rp3d::OverlapCallback::OverlapPair::EventType::OverlapExit:
            if (bhv1) {
                if (bhv1->GetIsActiveAndEnabled()) {
                    bhv1->OnOverlapExit(collider1, collider2, pair);
                }
            }
            if (bhv2) {
                if (bhv2->GetIsActiveAndEnabled()) {
                    bhv2->OnOverlapExit(collider2, collider1, pair);
                }
            }
            break;
        default:
            std::cout << "rp3d::CollisionCallback::ContactPair::EventType error" << std::endl;
            break;
        }
        // std::cout << "trigger" << std::endl;
    }
}
