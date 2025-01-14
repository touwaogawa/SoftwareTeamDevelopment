#pragma once

class Scene;

class SceneManager {
public:
    /// @brief Set the next scene
    /// @param nextScene
    static void LoadScene(Scene* nextScene);

    /// @brief Check if the LoadSecne method was called
    /// @return return true if the LoadScene methos was called, otherwise return false
    static bool GetiIsChanged();

    /// @brief Adopt the next scene
    static void AdoptSceneChange();

    /// @brief Return the current scene
    /// @return The pointer of the current scene
    static Scene* GetCurrentScene() { return mCurrentScene; }

private:
    static Scene* mCurrentScene;
    static Scene* mNextScene;
    static bool mIsChanged;
};