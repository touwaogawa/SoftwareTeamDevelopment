#include "rider.h"
#include "../../component.h"
#include "../../components/meshRenderer.h"
#include "../../components/transform.h"
#include "riderMove.h"
// #include "riderMove.h"

Rider::Rider(Scene* scene, Transform* parent)
    : GameObject(scene, parent, new RiderMove(this))
    , mMeshRenderer(new MeshRenderer(this))
{
    AddComponent(mMeshRenderer);
    // mMeshRenderer->Load("assets/models/BaseHuman.obj");
    mMeshRenderer->Load("assets/models/BaseHuman.obj");
}

Rider::~Rider()
{
}