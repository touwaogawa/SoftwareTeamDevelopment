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
    mRootObjects.clear();
}
void Scene::Start()
{
    // for (GameObject* gameObject : mRootObjects) {
    //     StartgameScriptsFromRoot(gameObject);
    // }
}
void Scene::Update(bool& exitFrag, float timeStep_sec)
{
    // ゲームオブジェクトの更新

    for (GameObject* gameObject : mRootObjects) {
        std::cout << "ppp" << std::endl;
        UpdategameScriptsFromRoot(gameObject);
    }
    // 物理演算
    mPhysics->Update(timeStep_sec);
    // ゲームオブジェクトの更新(物理演算終了後)
    for (GameObject* gameObject : mRootObjects) {
        LateUpdategameScriptsFromRoot(gameObject);
    }
}

void Scene::Instantiate(GameObject* original, Transform* parent, bool instantiateInWorldSpace)
{
    // std::cout << "a" << std::endl;
    if (original) {
        // std::cout << "b" << std::endl;
        original->SetScene(this);
        original->GetTransform()->SetParent(parent, instantiateInWorldSpace);
        Behaviour* bhv = original->GetBehaviour();
        if (bhv) {
            // std::cout << "c" << std::endl;
            bhv->Awake();
            // std::cout << "d" << std::endl;
            if (original->GetIsActive() || bhv->GetEnabled()) {
                // std::cout << "e" << std::endl;
                bhv->OnEnable();
            }
            // std::cout << "f" << std::endl;
        }
    }
}
void Scene::Instantiate(GameObject* original, Matrix4 transform, Transform* parent)
{
    if (original) {
        original->SetScene(this);
        original->GetTransform()->SetParent(parent);
        original->GetTransform()->SetWorldMatrix(transform);
        Behaviour* bhv = original->GetBehaviour();
        if (bhv) {
            bhv->Awake();
            if (original->GetIsActive() || bhv->GetEnabled()) {
                bhv->OnEnable();
            }
        }
    }
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
    if (rootObject->GetIsActive()) {
        std::cout << "active" << std::endl;
        Behaviour* bhv = rootObject->GetBehaviour();
        if (bhv) {
            std::cout << "bhv" << std::endl;
            if (bhv->GetEnabled()) {
                std::cout << "enabled" << std::endl;
                if (bhv->GetState() == BehaviourState::PreStart) {
                    bhv->Start();
                    bhv->SetState(BehaviourState::Started);
                }
                bhv->Update();
            }
        }
        for (Transform* transform : rootObject->GetTransform()->GetChildren()) {
            UpdategameScriptsFromRoot(transform->GetOwner());
        }
    }
}
void Scene::LateUpdategameScriptsFromRoot(GameObject* rootObject)
{
    if (rootObject->GetIsActive()) {
        Behaviour* bhv = rootObject->GetBehaviour();
        if (bhv) {
            if (bhv->GetEnabled()) {
                rootObject->GetBehaviour()->LateUpdate();
            }
        }
        for (Transform* transform : rootObject->GetTransform()->GetChildren()) {
            LateUpdategameScriptsFromRoot(transform->GetOwner());
        }
    }
}