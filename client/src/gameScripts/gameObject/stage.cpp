#include "stage.h"
#include "../../../../common/src/component/rigidBody.h"
#include "../../../../common/src/physics.h"
#include "../../../../utils/src/math.h"
#include "../../component/meshRenderer.h"
#include <reactphysics3d/reactphysics3d.h>
#include <tiny_obj_loader.h>
#include <vector>

Stage::Stage(Physics* physics, const std::string& meshFileName, const std::string& textureFileName)
    : GameObject("Stage")
{
    // meshrenderer
    AddComponent(new MeshRenderer(this, meshFileName, textureFileName));

    // RigidBody setting
    RigidBody* rigidBody  = new RigidBody(this, rp3d::BodyType::STATIC, physics);
    rp3d::RigidBody* rprb = rigidBody->GetRp3dRogidBody();
    rprb->setIsAllowedToSleep(false);
    rp3d::Vector3 position(0.0, 0.0, 0.0);
    rp3d::Quaternion rotation(rp3d::Quaternion::identity()); // 回転なし
    rp3d::Transform offset(position, rotation);

    // メッシュ生成//
    std::vector<Vector3> vertices = LoadObjFile(meshFileName);
    rp3d::VertexArray va          = rp3d::VertexArray(vertices.data(), sizeof(Vector3), vertices.size(), rp3d::VertexArray::DataType::VERTEX_FLOAT_TYPE);
    std::vector<rp3d::Message> messages;
    rp3d::ConvexMesh* cm = physics->GetPhysicsCommon().createConvexMesh(va, messages);
    for (const auto& message : messages) {
        std::cout << message.text << std::endl;
    }
    rp3d::CollisionShape* shape = physics->GetPhysicsCommon().createConvexMeshShape(cm, rp3d::Vector3(1.0f, 1.0f, 1.0f));

    // メッシュ代入
    rp3d::Collider* collider = rprb->addCollider(shape, offset);
    collider->getMaterial().setFrictionCoefficient(1.0f);
    collider->getMaterial().setBounciness(0.0f);
    AddComponent(rigidBody);
}

std::vector<Vector3> Stage::LoadObjFile(const std::string& fileName)
{
    // tinyobjのオブジェクト作成
    tinyobj::ObjReader reader;
    if (!reader.ParseFromFile(fileName)) {
        if (!reader.Error().empty()) {
            std::cerr << "Error loading OBJ file: " << reader.Error() << std::endl;
        }
        // return {}; // エラー時は空のベクトルを返す
    }

    // モデルデータを取得
    const auto& shapes = reader.GetShapes();
    const auto& attrib = reader.GetAttrib();
    std::vector<Vector3> vertices;

    // 頂点データを読み込み
    for (size_t i = 0; i < shapes.size(); ++i) {
        const auto& shape = shapes[i];

        for (size_t j = 0; j < shape.mesh.indices.size(); ++j) {
            const auto& idx = shape.mesh.indices[j];

            // 頂点位置の取得
            Vector3 position(
                attrib.vertices[idx.vertex_index * 3],
                attrib.vertices[idx.vertex_index * 3 + 1],
                attrib.vertices[idx.vertex_index * 3 + 2]);
            vertices.push_back(position);
        }
    }
    return vertices;
}
