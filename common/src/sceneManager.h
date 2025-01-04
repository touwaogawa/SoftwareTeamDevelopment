#pragma once
class SceneManager {
public:
    static void LoadScene(class Scene* nextScene);
    static bool GetiIsChanged();
    static void AdoptSceneChange();
    static class Scene* GetCurrentScene();

private:
    static class Scene* mCurrentScene;
    static class Scene* mNextScene;
    static bool mIsChanged;
};