#include "scene.h"
#include "../../common/src/components/behaviour.h"
#include "../../common/src/gameObject.h"
#include "renderer.h"
#include <algorithm>
//
#include <iostream>
Scene::Scene(std::string name)
    : currentFrame(0)
    , mName(name)
{
    std::cout << "scene1" << std::endl;
    mRenderer = new Renderer();
    std::cout << "scene2" << std::endl;
}

Scene::~Scene()
{
    std::cout << "~scene1" << std::endl;
    RemoveAllObject();
    std::cout << "~scene2" << std::endl;
    delete mRenderer;
    std::cout << "~scene3" << std::endl;
}
void Scene::ProccessNetowork()
{
    return;
}
void Scene::Start()
{
    for (GameObject* gameObject : mGameObjects) {
        if (gameObject->GetBehaviour() != nullptr)
            gameObject->GetBehaviour()->Start();
    }
}

void Scene::Update()
{
    for (GameObject* gameObject : mGameObjects) {
        if (gameObject->GetBehaviour() != nullptr)
            gameObject->GetBehaviour()->Update();
    }
}
void Scene::LateUpdate()
{
    for (GameObject* gameObject : mGameObjects) {
        if (gameObject->GetBehaviour() != nullptr)
            gameObject->GetBehaviour()->LateUpdate();
    }
}

void Scene::Draw()
{
    mRenderer->Draw();
}

Renderer* Scene::GetRenderer() const
{
    return mRenderer;
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
void Scene::RemoveAllObject()
{
    for (GameObject* rootObject : mRootObjects) {
        RemoveRootObject(rootObject);
    }
}