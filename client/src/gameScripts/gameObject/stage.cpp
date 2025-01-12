#include "stage.h"
#include "../../component/meshRenderer.h"

Stage_C::Stage_C(Physics* physics, const std::string& meshFileName, const std::string& imageFileName, bool isConvex)
    : Stage(physics, meshFileName)
{
    AddComponent(new MeshRenderer(this, meshFileName, imageFileName));
}