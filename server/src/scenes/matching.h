#pragma once
#include "../../../common/src/scene.h"
#include <enet/enet.h>
#include <vector>

enum class MatchingState {
    Init,
    Waiting,
    AllConnected,
    MatchingStateNum
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
    bool ProccessNetowork();

    ENetAddress address;
    ENetHost* server;
};