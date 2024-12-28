#include "stage.h"
#include "../../../../client/src/components/meshRenderer.h"
#include "../../../../common/src/component.h"
#include "../../components/transform.h"

Stage::Stage(Scene* scene, Transform* parent)
    : GameObject(scene, parent, nullptr)
    , mMeshRenderer(new MeshRenderer(this))
    , mGravity(10)
{
    AddComponent(mMeshRenderer);
    mMeshRenderer->Load("../assets/models/Stage.obj");
}

Stage::~Stage()
{
}

float Stage::GetGravity() const
{
    return mGravity;
}