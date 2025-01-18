#pragma once
#include "../../../../common/src/gameScripts/gameObject/player.h"
#include "../../../../common/src/scene.h"
#include <enet/enet.h>
#include <map>
#include <unordered_map>
#include <vector>

class Stage;

enum class BattleState {
    CountDown,
    Battle,
    BattleStateNum
};

class BattleScene : public Scene {
public:
    BattleScene(int playerNum, std::vector<PlayerInfo> playerInfos);
    ~BattleScene() override;
    bool Load() override;
    void SetENet(ENetAddress address, ENetHost* Server);
    void Update(bool& exitFrag, float timeStep) override;
    Stage* GetStage() const;
    int GetPlayerNum() const;

private:
    BattleState mBattleState = BattleState::CountDown;
    const int mPlayerNum;
    std::map<int, PlayerState> mPlayerStates;
    //<frame, <id, commandData>>
    std::map<int, std::unordered_map<int, class CommandData>> mPlayerCommandsBuffer;

    ENetEvent mENetEvent;
    ENetAddress mAddress;
    ENetHost* mServer;

    bool ProccessInput();
    bool ProccessNetowork();
};