#pragma once

class SceneManager {
public:
    static void LoadScene(class Scene* nextScene);

    static class Scene* GetCurrentScene();

private:
    static class Scene* mCurrentScene;
};