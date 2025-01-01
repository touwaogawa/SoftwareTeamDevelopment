#pragma once
#include "../../../common/src/scene.h"
#include <enet/enet.h>
#include <queue>
#include <utility>

enum class MatchingState {
    Init,
    Connecting,
    Connected,
};

class MatchingScene : public Scene {
public:
    MatchingScene();
    ~MatchingScene() override;
    bool Load() override;

    void Update(bool& exitFrag) override;

private:
    MatchingState mMatchingState;
    bool ProccessInput();
    bool ProccessNetowork();

    int battleId;
    ENetAddress address;
    ENetHost* client;
    ENetPeer* peer;
};