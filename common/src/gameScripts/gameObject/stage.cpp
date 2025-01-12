#include "stage.h"
#include "../../component/rigidBody.h"
#include "../../physics.h"

Stage::Stage(Physics* physics, const std::string& meshFileName)
    : GameObject()
{
    // RigidBody setting
    RigidBody* rigidBody  = new RigidBody(this, rp3d::BodyType::STATIC, physics);
    rp3d::RigidBody* rprb = rigidBody->GetRp3dRogidBody();

    // Collider setting
    rp3d::Vector3 position(0.0f, 0.0f, 0.0f);
    rp3d::Quaternion rotation; // 回転なし
    rp3d::Transform offset(position, rotation);

    // メッシュ生成//
    // rp3d::CollisionShape* shape = physics->GetPhysicsCommon().createConvexMeshShape(convexMesh, rp3d::Vector3(1.0f, 1.0f, 1.0f));

    // rprb->addCollider(shape, offset);

    AddComponent(rigidBody);
}

Stage::~Stage()
{
}