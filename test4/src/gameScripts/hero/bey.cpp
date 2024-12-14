#include "bey.h"
#include "../../component.h"
#include "../../components/meshRenderer.h"
#include "../../components/transform.h"

Bey::Bey(Scene* scene, Transform* parent)
    : GameObject(scene, parent, nullptr)
    , mMeshRenderer(new MeshRenderer(this))
{
    AddComponent(mMeshRenderer);
    mMeshRenderer->Load("assets/models/Cube.obj");
}

Bey::~Bey()
{
}