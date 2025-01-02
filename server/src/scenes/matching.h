#pragma once
#include "../../../common/src/gamescripts/player.h"
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
    MatchingScene(int playerNum);
    ~MatchingScene() override;
    bool Load() override;
    void Update(bool& exitFrag) override;

private:
    MatchingState mMatchingState;
    bool ProccessInput();
    bool ProccessNetowork();

    ENetAddress mAddress;
    ENetHost* mServer;
    std::map<int, ENetPeer*> mClientID_Peer;
    int mPlayerNum;
    std::vector<PlayerInfo> mPlayerInfos;
    int mStartCount = 10;
};