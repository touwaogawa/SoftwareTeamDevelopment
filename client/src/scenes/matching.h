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

private:
    void BeforeUpdateGameObject() override;
    void AfterUpdateGameObject() override;
    MatchingState mMatchingState;
    bool ProccessInput();
    bool ProccessNetowork();

    ENetAddress address;
    ENetHost* client;
    ENetPeer* peer;

    void DestroyPackets();
    std::queue<std::pair<int, ENetPacket*>> mPendingPakets;
};