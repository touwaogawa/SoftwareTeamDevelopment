#include "staticModel.h"
#include "../../../../common/src/component/transform.h"
#include "../../component/meshRenderer.h"

StaticModel::StaticModel(Scene* scene, Transform* parent, const Matrix4& initialTransform, const std::string& objFileName, const std::string& imageFileName)
    : GameObject(scene, parent)
{
    AddComponent(new MeshRenderer(this, objFileName, imageFileName));
    mTransform->SetWorldMatrix(initialTransform);
}
StaticModel::~StaticModel()
{
}