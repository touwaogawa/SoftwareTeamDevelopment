#include "simpleMeshModel.h"
#include "../../../../common/src/component/transform.h"
#include "../../component/meshRenderer.h"

SimpleMeshModel::SimpleMeshModel(const std::string& objFileName, const std::string& imageFileName)
    : GameObject()
{
    AddComponent(new MeshRenderer(this, objFileName, imageFileName));
}
SimpleMeshModel::~SimpleMeshModel()
{
}