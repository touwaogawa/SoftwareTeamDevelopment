#pragma once
#include "../../../../common/src/gameScripts/playerInfo.h"
#include "../../../../common/src/scene.h"
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
    MatchingScene(int playerNum);
    MatchingScene(int playerNum, ENetAddress address, ENetHost* Server);
    ~MatchingScene() override;
    bool Load() override;
    void Update(bool& exitFrag, float timeStep) override;

private:
    MatchingState mMatchingState;
    const int mPlayerNum;
    int mStartCount;

    ENetAddress mAddress;
    ENetHost* mServer;

    ENetEvent mENetEvent;

    std::map<int, ENetPeer*> mClientID_Peer;

    std::vector<PlayerInfo> mPlayerInfos;

    bool ProccessInput();
    bool ProccessNetowork();
};