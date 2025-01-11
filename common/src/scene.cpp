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
    DeteleAllObject();
}
void Scene::Start()
{
    for (GameObject* gameObject : mRootObjects) {
        StartgameScriptsFromRoot(gameObject);
    }
}
void Scene::Update(bool& exitFrag, float timeStep_sec)
{
    // ゲームオブジェクトの更新
    for (GameObject* gameObject : mRootObjects) {
        UpdategameScriptsFromRoot(gameObject);
    }
    // 物理演算
    mPhysics->Update(timeStep_sec);
    // ゲームオブジェクトの更新(物理演算終了後)
    for (GameObject* gameObject : mRootObjects) {
        LateUpdategameScriptsFromRoot(gameObject);
    }
}

void Scene::AddGameObject(GameObject* gameObject)
{
    mGameObjects.push_back(gameObject);
    // std::cout << "go num : " << mGameObjects.size() << std::endl;
}

void Scene::RemoveGameObject(GameObject* gameObject)
{
    auto end = std::remove(mGameObjects.begin(), mGameObjects.end(), gameObject);
    mGameObjects.erase(end, mGameObjects.end());
    // std::cout << "go num : " << mGameObjects.size() << std::endl;
}

void Scene::AddRootObject(GameObject* gameObject)
{
    mRootObjects.push_back(gameObject);
    // std::cout << "ro num : " << mRootObjects.size() << std::endl;
}

void Scene::RemoveRootObject(GameObject* gameObject)
{

    auto end = std::remove(mRootObjects.begin(), mRootObjects.end(), gameObject);
    mRootObjects.erase(end, mRootObjects.end());
    // std::cout << "ro num : " << mRootObjects.size() << std::endl;
}

std::string Scene::GetName() const
{
    return mName;
}

// protected ###################
void Scene::DeteleAllObject()
{
    for (GameObject* rootObject : mRootObjects) {
        // std::cout << "root Object" << std::endl;
        delete rootObject;
    }
}

// private ######################
void Scene::StartgameScriptsFromRoot(GameObject* rootObject)
{
    if (rootObject->GetBehaviour()) {
        rootObject->GetBehaviour()->Start();
    }
    for (Transform* transform : rootObject->GetTransform()->GetChildren()) {
        StartgameScriptsFromRoot(transform->GetOwner());
    }
}
void Scene::UpdategameScriptsFromRoot(GameObject* rootObject)
{
    if (rootObject->GetBehaviour()) {
        rootObject->GetBehaviour()->Update();
    }
    for (Transform* transform : rootObject->GetTransform()->GetChildren()) {
        UpdategameScriptsFromRoot(transform->GetOwner());
    }
}
void Scene::LateUpdategameScriptsFromRoot(GameObject* rootObject)
{
    if (rootObject->GetBehaviour()) {
        rootObject->GetBehaviour()->LateUpdate();
    }
    for (Transform* transform : rootObject->GetTransform()->GetChildren()) {
        LateUpdategameScriptsFromRoot(transform->GetOwner());
    }
}