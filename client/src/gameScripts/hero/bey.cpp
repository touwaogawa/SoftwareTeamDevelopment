#include "bey.h"
#include "../../component.h"
#include "../../components/meshRenderer.h"
#include "../../components/transform.h"
#include "beyMove.h"

Bey::Bey(Scene* scene, Transform* parent)
    : GameObject(scene, parent, new BeyMove(this))
    , mMeshRenderer(new MeshRenderer(this))
{
    AddComponent(mMeshRenderer);
    mMeshRenderer->Load("assets/models/BaseHuman.obj");
}

Bey::~Bey()
{
}