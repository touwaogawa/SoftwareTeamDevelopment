#include "sceneManager.h"
#include "scene.h"
#include <iostream>
Scene* SceneManager::mCurrentScene = nullptr;
Scene* SceneManager::mNextScene    = nullptr;
bool SceneManager::mIsChanged      = false;

void SceneManager::LoadScene(Scene* nextScene)
{
    mNextScene = nextScene;
    mIsChanged = true;
}
bool SceneManager::GetiIsChanged()
{
    return mIsChanged;
}
void SceneManager::AdoptSceneChange()
{
    if (mCurrentScene != nullptr) {
        delete mCurrentScene;
    }
    mCurrentScene = mNextScene;
    if (!mCurrentScene->Load()) {
        std::cout << "Failed Scene load : " << mCurrentScene->GetName() << std::endl;
    }
    mCurrentScene->Start();
    mIsChanged = false;
}
Scene* SceneManager::GetCurrentScene()
{
    return mCurrentScene;
}