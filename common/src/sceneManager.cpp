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
            delete mCurrentScene;
        }
    }
    return mIsChanged;
}
void SceneManager::AdoptSceneChange()
{
    mCurrentScene = mNextScene;
    if (!mCurrentScene->Load()) {
        std::cout << "Failed Scene load : " << mCurrentScene->GetName() << std::endl;
    }
    mIsChanged = false;
}