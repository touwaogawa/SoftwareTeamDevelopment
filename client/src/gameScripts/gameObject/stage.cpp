#include "stage.h"
#include "../../component/meshRenderer.h"

Stage_C::Stage_C(Scene* scene, Transform* parent)
    : Stage(scene, parent)
{
    AddComponent(new MeshRenderer(this, "../assets/models/Stage.obj"));
}