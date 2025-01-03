#include "scene.h"
#include "../../common/src/components/behaviour.h"
#include "../../common/src/components/transform.h"
#include "../../common/src/gameObject.h"
#include <algorithm>
//
#include <iostream>
Scene::Scene(std::string name)
    : currentFrame(0)
    , mName(name)
{
}

Scene::~Scene()
{
    RemoveAllObject();
}
void Scene::Start()
{
    for (GameObject* gameObject : mRootObjects) {
        StartGameObjectsFromRoot(gameObject);
    }
}
void Scene::Update(bool& exitFrag)
{
    for (GameObject* gameObject : mRootObjects) {
        UpdateGameObjectsFromRoot(gameObject);
    }
    for (GameObject* gameObject : mRootObjects) {
        LateUpdateGameObjectsFromRoot(gameObject);
    }
}

void Scene::AddGameObject(GameObject* gameObject)
{
    mGameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(GameObject* gameObject)
{
    auto end = std::remove(mGameObjects.begin(), mGameObjects.end(), gameObject);
    mGameObjects.erase(end, mGameObjects.end());
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
void Scene::StartGameObjectsFromRoot(GameObject* rootObject)
{
    if (rootObject->GetBehaviour() != nullptr) {
        rootObject->GetBehaviour()->Start();
    }
    for (Transform* transform : rootObject->GetTransform()->GetChildren()) {
        StartGameObjectsFromRoot(transform->GetOwner());
    }
}
void Scene::UpdateGameObjectsFromRoot(GameObject* rootObject)
{
    if (rootObject->GetBehaviour() != nullptr) {
        rootObject->GetBehaviour()->Update();
    }
    for (Transform* transform : rootObject->GetTransform()->GetChildren()) {
        UpdateGameObjectsFromRoot(transform->GetOwner());
    }
}
void Scene::LateUpdateGameObjectsFromRoot(GameObject* rootObject)
{
    if (rootObject->GetBehaviour() != nullptr) {
        rootObject->GetBehaviour()->LateUpdate();
    }
    for (Transform* transform : rootObject->GetTransform()->GetChildren()) {
        LateUpdateGameObjectsFromRoot(transform->GetOwner());
    }
}