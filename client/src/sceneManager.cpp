#include "sceneManager.h"
#include "scene.h"

Scene* SceneManager::mCurrentScene = nullptr;

void SceneManager::LoadScene(Scene* nextScene)
{
    delete mCurrentScene;
    mCurrentScene = nextScene;
}

Scene* SceneManager::GetCurrentScene()
{
    return mCurrentScene;
}