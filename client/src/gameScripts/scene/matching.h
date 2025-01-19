#pragma once
#include "../../../../common/src/gameScripts/playerInfo.h"
#include "../../../../common/src/scene.h"
#include "../gameObject/player.h"
#include <enet/enet.h>
#include <queue>
#include <utility>

class GameObject;
enum class MatchingState {
    Init,
    Connecting,
    Connected,
    StartBattle,
    MatchingStateNum,
};

class MatchingScene : public Scene {
public:
    MatchingScene();
    ~MatchingScene() override = default;
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

    int mStartCount;
};