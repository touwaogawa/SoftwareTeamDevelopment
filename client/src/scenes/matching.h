#pragma once
#include "../../../common/src/scene.h"
#include <vector>

enum class MatchingState {
    Connecting,
    Connected,
};

class MatchingScene : public Scene {
public:
    MatchingScene();
    ~MatchingScene() override;
    bool Load() override;

private:
    void BeforeUpdateGameObject() override;
    void AfterUpdateGameObject() override;
    MatchingState mMatchingState;
    bool ProccessInput();
    void ProccessNetowork();
};