#include "scene.h"
#include "components/behaviour.h"
#include "gameObject.h"
#include "renderer.h"
#include <algorithm>

Scene::Scene()
{
    mRenderer = new Renderer();
}

Scene::~Scene()
{
    delete mRenderer;
}

bool Scene::Load()
{
    mRenderer->Load();
    return false;
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