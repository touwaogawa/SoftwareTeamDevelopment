#pragma once
#include "../../../../common/src/gameScripts/gameObject/player.h"
#include "../../../../common/src/scene.h"
#include <enet/enet.h>
#include <queue>
#include <utility>

class GameObject;
enum class MatchingState {
    Init,
    Connecting,
    Connected,
    MatchingStateNum
};

class MatchingScene : public Scene {
public:
    MatchingScene();
    ~MatchingScene() override;
    bool Load() override;

    void Update(bool& exitFrag, float timeStep) override;

private:
    MatchingState mMatchingState;

    ENetEvent mENetEvent;

    ENetAddress mAddress;
    ENetHost* mClient;
    ENetPeer* mPeer;
    int myPlayerId;

    std::vector<PlayerInfo> mPlayerInfos;

    bool ProccessInput();
    bool ProccessNetowork();

    GameObject* mConnectingSprite;
    GameObject* mMatchingSprite;
    GameObject* mPreStartSprite;

    class Player* mPlayer;
};