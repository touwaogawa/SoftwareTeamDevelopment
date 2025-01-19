#include "hitBox.h"
#include "../../../../common/src/component/rigidBody.h"
#include "../../../../common/src/physics.h"
#include "../../../../common/src/scene.h"
#include "../../../../common/src/sceneManager.h"
#include "../components/behaviour/hitBoxMove.h"

HitBox::HitBox(Hero* ownerHero, const std::string& ignoreTag, float radius, Vector3 hitVector, float damage, int destroyFrame, int& actionFrame)
    : GameObject("HitBox")
{
    // RigidBody setting
    rp3d::PhysicsCommon& pCommon = SceneManager::GetCurrentScene()->GetPhysics()->GetPhysicsCommon();
    RigidBody* rigidBody         = new RigidBody(this, rp3d::BodyType::KINEMATIC, SceneManager::GetCurrentScene()->GetPhysics());
    rp3d::RigidBody* rprb        = rigidBody->GetRp3dRogidBody();

    rp3d::Vector3 position(0.0f, 0.0f, 0.0f);
    rp3d::Quaternion rotation(rp3d::Quaternion::identity());
    rp3d::Transform offset(position, rotation);

    // collider
    rp3d::SphereShape* shape = pCommon.createSphereShape(radius);
    rp3d::Collider* collider = rprb->addCollider(shape, offset);
    collider->setIsTrigger(true);
    // ignore collision
    AddComponent(rigidBody);

    SetBehaviour(new HitBoxMove(ownerHero, this, ignoreTag, hitVector, damage, destroyFrame, actionFrame));
}