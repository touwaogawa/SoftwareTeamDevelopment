#pragma once
#include "../../../common/src/scene.h"
#include <enet/enet.h>
#include <map>
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
    void Update(bool& exitFrag) override;

private:
    MatchingState mMatchingState;
    bool ProccessInput();
    bool ProccessNetowork();

    ENetAddress address;
    ENetHost* server;
    std::map<int, ENetPeer*> ClientID;
};