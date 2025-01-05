#include "scene.h"
#include "component/behaviour.h"
#include "component/transform.h"
#include "gameObject.h"
#include "physics.h"
#include <algorithm>
//
#include <iostream>
Scene::Scene(std::string name)
    : currentFrame(0)
    , mName(name)
    , mPhysics(new Physics())
{
}

Scene::~Scene()
{
    delete mPhysics;
    RemoveAllObject();
}
void Scene::Start()
{
    for (GameObject* gameObject : mRootObjects) {
        StartgameScriptsFromRoot(gameObject);
    }
}
void Scene::Update(bool& exitFrag, float timeStep)
{
    // ゲームオブジェクトの更新
    for (GameObject* gameObject : mRootObjects) {
        UpdategameScriptsFromRoot(gameObject);
    }
    // 物理演算
    mPhysics->Update(timeStep);
    // ゲームオブジェクトの更新(物理演算終了後)
    for (GameObject* gameObject : mRootObjects) {
        LateUpdategameScriptsFromRoot(gameObject);
    }
}

void Scene::AddGameObject(GameObject* gameObject)
{
    mgameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(GameObject* gameObject)
{
    auto end = std::remove(mgameObjects.begin(), mgameObjects.end(), gameObject);
    mgameObjects.erase(end, mgameObjects.end());
}

void Scene::AddRootObject(GameObject* gameObject)
{
    mRootObjects.push_back(gameObject);
}

void Scene::RemoveRootObject(GameObject* gameObject)
{
    auto end = std::remove(mRootObjects.begin(), mRootObjects.end(), gameObject);
    mRootObjects.erase(end, mRootObjects.end());
}

std::string Scene::GetName() const
{
    return mName;
}

// protected ###################

void Scene::RemoveAllObject()
{
    for (GameObject* rootObject : mRootObjects) {
        RemoveRootObject(rootObject);
    }
}

// private ######################
void Scene::StartgameScriptsFromRoot(GameObject* rootObject)
{
    if (rootObject->GetBehaviour() != nullptr) {
        rootObject->GetBehaviour()->Start();
    }
    for (Transform* transform : rootObject->GetTransform()->GetChildren()) {
        StartgameScriptsFromRoot(transform->GetOwner());
    }
}
void Scene::UpdategameScriptsFromRoot(GameObject* rootObject)
{
    if (rootObject->GetBehaviour() != nullptr) {
        rootObject->GetBehaviour()->Update();
    }
    for (Transform* transform : rootObject->GetTransform()->GetChildren()) {
        UpdategameScriptsFromRoot(transform->GetOwner());
    }
}
void Scene::LateUpdategameScriptsFromRoot(GameObject* rootObject)
{
    if (rootObject->GetBehaviour() != nullptr) {
        rootObject->GetBehaviour()->LateUpdate();
    }
    for (Transform* transform : rootObject->GetTransform()->GetChildren()) {
        LateUpdategameScriptsFromRoot(transform->GetOwner());
    }
}