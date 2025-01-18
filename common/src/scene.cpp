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
    // std::cout << "~Scene : " << mName << std::endl;
    DeteleAllObject();
    // std::cout << "~Scene : " << mName << std::endl;
    if (mPhysics)
        delete mPhysics;
    // std::cout << "~Scene : " << mName << std::endl;
}

void Scene::Update(bool& exitFrag, float timeStep_sec)
{
    // ゲームオブジェクトの更新

    // std::cout << "object update" << std::endl;
    for (GameObject* gameObject : mGameObjects) {
        // std::cout << "object update : " << gameObject->GetName() << std::endl;
        if (!gameObject->GetTransform()->GetParent())
            UpdategameScriptsFromRoot(gameObject);
        // if (gameObject->GetTransform()->GetParent())
        // std::cout << "???" << std::endl;
    }
    // std::cout << "physics update" << std::endl;
    // 物理演算
    mPhysics->Update(timeStep_sec);
    // ゲームオブジェクトの更新(物理演算終了後)
    // std::cout << "object late update" << std::endl;
    for (GameObject* gameObject : mGameObjects) {
        // std::cout << "object late update in" << std::endl;
        if (!gameObject->GetTransform()->GetParent())
            LateUpdategameScriptsFromRoot(gameObject);
    }
    // std::cout << "object destroy" << std::endl;
    for (GameObject* destroyObject : mDestroyObjects) {
        // std::cout << "object destroy in" << std::endl;
        delete destroyObject;
    }
    mDestroyObjects.clear();
}

// GameObject& Scene::Instantiate(GameObject original, Transform* parent, bool instantiateInWorldSpace)
// {
//     GameObject* clone = new GameObject(original.GetName(), original.GetTag(), original.GetIsActive());
//     clone->SetScene(this);
//     AddGameObject(clone);
//     clone->GetTransform()->SetParent(parent, instantiateInWorldSpace);
//     Behaviour* bhv = clone->GetBehaviour();
//     if (bhv) {
//         bhv->Awake();
//         if (clone->GetIsActive() || bhv->GetEnabled()) {
//             bhv->OnEnable();
//         }
//     }
//     return *clone;
// }
// GameObject& Scene::Instantiate(GameObject original, Vector3 position, Quaternion rotation, Transform* parent)
// {
//     GameObject* clone = new GameObject(original.GetName(), original.GetTag(), original.GetIsActive());
//     clone->SetScene(this);
//     AddGameObject(clone);
//     clone->GetTransform()->SetWorldPosition(position);
//     clone->GetTransform()->SetParent(parent);
//     Behaviour* bhv = clone->GetBehaviour();
//     if (bhv) {
//         bhv->Awake();
//         if (clone->GetIsActive() || bhv->GetEnabled()) {
//             bhv->OnEnable();
//         }
//     }
//     return *clone;
// }

void Scene::AddGameObject(GameObject* gameObject)
{
    mGameObjects.push_back(gameObject);
    // std::cout << "gemobjects num : " << mGameObjects.size() << std::endl;
}

void Scene::RemoveGameObject(GameObject* gameObject)
{

    auto end = std::remove(mGameObjects.begin(), mGameObjects.end(), gameObject);
    mGameObjects.erase(end, mGameObjects.end());
    // std::cout << "ro num : " << mRootObjects.size() << std::endl;
}

std::string Scene::GetName() const
{
    return mName;
}

// protected ###################
void Scene::DeteleAllObject()
{
    for (GameObject* gameObject : mGameObjects) {
        // std::cout << "root Object" << std::endl;
        delete gameObject;
    }
    // std::cout << "rooect" << std::endl;
    mGameObjects.clear();
    // std::cout << "rootct" << std::endl;
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
    // std::cout << "name : " << rootObject->GetName() << std::endl;

    if (rootObject->GetIsActive()) {
        // std::cout << "active" << std::endl;
        Behaviour* bhv = rootObject->GetBehaviour();
        if (bhv) {
            // std::cout << "bhv" << std::endl;
            if (bhv->GetEnabled()) {
                // std::cout << "enabled" << std::endl;
                if (bhv->GetState() == BehaviourState::PreStart) {
                    // std::cout << "start" << std::endl;
                    bhv->Start();
                    bhv->SetState(BehaviourState::Started);
                }
                // std::cout << "bhv update" << std::endl;
                bhv->Update();
            }
        }
        // std::cout << "children" << std::endl;
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