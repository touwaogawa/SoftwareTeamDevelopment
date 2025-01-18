#pragma once
#include "../../../../common/src/scene.h"
#include "../../../../utils/src/math.h"
#include "../gameObject/hero.h"
#include "../gameObject/player.h"
#include <enet/enet.h>
#include <map>
#include <queue>
#include <unordered_map>
#include <vector>

class Stage;
enum class BattleState {
    CountDown,
    Battle,
    Result,
    BattleStateNum
};

struct BattlePlayerStatus {
    PlayerState playerState;
    HeroCurrentStatus heroStatus;
    CommandData commandData;
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

    const std::vector<Player*>& GetPlayers() { return mPlayers; }
    void SetNextBattleState(BattleState nextBattleState) { mNextBattleState = nextBattleState; }

private:
    BattleState mBattleState;
    BattleState mNextBattleState;

    ENetEvent mENetEvent;

    const int mPlayerNum;
    int mConnectPlayerNum;

    const int mMyPlayerID;
    std::vector<Player*> mPlayers;
    // <id, <frame, commanddata>>
    std::unordered_map<int, std::map<int, class CommandData>> mPlayerCommands;

    std::vector<BattlePlayerStatus> mPlayerSnapshot;

    ENetAddress mAddress;
    ENetHost* mClient;
    ENetPeer* mPeer;

    std::vector<struct PlayerInfo> mPlayerInfos;

    Player* mPlayer;
    Stage* mStage;

    bool ProccessInput();
    bool ProccessNetowork();
};