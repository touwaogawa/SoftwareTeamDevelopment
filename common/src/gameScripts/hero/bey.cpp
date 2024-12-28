#include "bey.h"
#include "../../../../client/src/components/meshRenderer.h"
#include "../../../../common/src/component.h"
#include "../../components/transform.h"
#include "beyMove.h"

Bey::Bey(class Scene* scene, class Transform* parent,
    float mass,
    float walkAcceleration,
    float maxWalkSpeed,
    float initialDushSpeed,
    float dushAcceleration,
    float maxRunSpeed,
    float traction)
    : GameObject(scene, parent, new BeyMove(this))
    , mMeshRenderer(new MeshRenderer(this))
    , mMass(mass)
    , mWalkAcceleration(walkAcceleration)
    , mMaxWalkSpeed(maxWalkSpeed)
    , mInitialDushSpeed(initialDushSpeed)
    , mDushAcceleration(dushAcceleration)
    , mMaxRunSpeed(maxRunSpeed)
    , mTraction(traction)
{
    AddComponent(mMeshRenderer);
    mMeshRenderer->Load("../assets/models/Shuriken.obj");
}

Bey::~Bey()
{
}