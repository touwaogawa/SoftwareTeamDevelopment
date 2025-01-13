#pragma once
#include "../../../../common/src/scene.h"
#include "../gameObject/hero.h"
#include "../gameObject/player.h"
#include <enet/enet.h>
#include <vector>

enum class BattleState {
    CountDown,
    Battle,
    BattleStateNum
};

class BattleScene : public Scene {
public:
    BattleScene(int myPlayerId, int playerNum, std::vector<PlayerInfo> playerInfos);
    ~BattleScene() override;
    bool Load() override;
    void SetENet(ENetAddress address, ENetHost* client, ENetPeer* peer);

    void Update(bool& exitFrag, float timeStep) override;

    class Stage* GetStage() const;
    int GetPlayerNum() const;

    const std::vector<class Player*>& GetPlayers() { return mPlayers; }

private:
    BattleState mBattleState;

    ENetEvent mENetEvent;

    const int mPlayerNum;
    const int mMyPlayerID;
    std::vector<class Player*> mPlayers;

    ENetAddress mAddress;
    ENetHost* mClient;
    ENetPeer* mPeer;

    std::vector<struct PlayerInfo> mPlayerInfos;

    class Player* mPlayer;
    class Stage* mStage;

    bool ProccessInput();
    bool ProccessNetowork();
};