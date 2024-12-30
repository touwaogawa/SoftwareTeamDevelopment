#include "scene.h"
#include "../../common/src/components/behaviour.h"
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
    for (GameObject* gameObject : mGameObjects) {
        if (gameObject->GetBehaviour() != nullptr)
            gameObject->GetBehaviour()->Start();
    }
}
void Scene::Update(bool& exitFrag)
{
    BeforeUpdateGameObject();
    UpdateGameObjects();
    LateUpdateGameObjects();
    AfterUpdateGameObject();
    currentFrame++;
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
void Scene::UpdateGameObjects()
{
    for (GameObject* gameObject : mGameObjects) {
        if (gameObject->GetBehaviour() != nullptr)
            gameObject->GetBehaviour()->Update();
    }
}
void Scene::LateUpdateGameObjects()
{
    for (GameObject* gameObject : mGameObjects) {
        if (gameObject->GetBehaviour() != nullptr)
            gameObject->GetBehaviour()->LateUpdate();
    }
}