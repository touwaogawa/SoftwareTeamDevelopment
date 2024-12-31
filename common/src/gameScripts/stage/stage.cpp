#include "stage.h"
#include "../../../../common/src/component.h"
#include "../../components/transform.h"

Stage::Stage(Scene* scene, Transform* parent)
    : GameObject(scene, parent, nullptr, GameObjectRenderType::Mesh3D, "../assets/models/Stage.obj")
{
}

Stage::~Stage()
{
}