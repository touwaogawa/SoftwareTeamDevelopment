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

    void Update(bool& exitFrag) override;

    class Stage* GetStage() const;
    int GetPlayerNum() const;

private:
    BattleState mBattleState = BattleState::CountDown;
    const int mPlayerNum;
    const int mMyPlayerID;
    std::vector<class Player_C*> mPlayers;

    ENetAddress mAddress;
    ENetHost* mClient;
    ENetPeer* mPeer;

    std::vector<struct PlayerInfo> mPlayerInfos;

    class Player_C* mPlayer;
    class Stage_C* mStage;

    bool ProccessInput();
    bool ProccessNetowork();
};