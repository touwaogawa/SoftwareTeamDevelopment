#include "simpleEffect.h"
#include "../../../../common/src/component/transform.h"
#include "../../component/meshRenderer.h"

SimpleEffect::SimpleEffect(const std::string& objFileName, const std::string& imageFileName)
    : GameObject()
{
    AddComponent(new MeshRenderer(this, objFileName, imageFileName, true));
}