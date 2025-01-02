#pragma once
#include "../../../common/src/gameScripts/hero/hero.h"
#include "../../../common/src/gameScripts/player.h"
#include "../../../common/src/scene.h"
#include <enet/enet.h>
#include <vector>

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
    void Update(bool& exitFrag) override;
    class Stage* GetStage() const;
    int GetPlayerNum() const;

private:
    BattleState mBattleState = BattleState::CountDown;
    const int mPlayerNum;
    std::vector<class Player*> mPlayers;
    class Stage* mStage;

    std::vector<PlayerInfo> mPlayerInfos;

    ENetAddress mAddress;
    ENetHost* mServer;

    bool ProccessInput();
    bool ProccessNetowork();
};