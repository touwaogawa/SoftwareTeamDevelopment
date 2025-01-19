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
    if (mIsChanged) {
        if (mCurrentScene) {
            // std::cout << "Scene deleted: " << mCurrentScene->GetName() << std::endl;
            delete mCurrentScene;
            // std::cout << "Scene deleted: " << mCurrentScene->GetName() << std::endl;
        }
    }
    return mIsChanged;
}
bool SceneManager::AdoptSceneChange()
{
    if (mNextScene) {
        mCurrentScene = mNextScene;
        // std::cout << "m next scene: " << mCurrentScene->GetName() << std::endl;
        if (!mCurrentScene->Load()) {
            // std::cout << "Failed Scene load : " << mCurrentScene->GetName() << std::endl;
        }
        // std::cout << "m next scene: " << mCurrentScene->GetName() << std::endl;
        mIsChanged = false;
        return true;
    } else {
        return false;
    }
}