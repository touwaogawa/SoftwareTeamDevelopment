#include "stage.h"
#include "../../../../common/src/component.h"
#include "../../components/transform.h"

Stage::Stage(Scene* scene, Transform* parent)
    : GameObject(scene, parent)
{
}

Stage::~Stage()
{
}