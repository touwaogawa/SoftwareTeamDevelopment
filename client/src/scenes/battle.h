#pragma once
#include "../gameScripts/hero/hero.h"
#include "../scene.h"
#include <vector>

class BattleScene : public Scene {
public:
    BattleScene(int myPlayerId, int playerNum);
    ~BattleScene() override;
    bool Load() override;
    bool ProccessInput() override;
    void ProccessNetowork() override;

    class Stage* GetStage() const;
    int GetPlayerNum() const;

private:
    const int mPlayerNum;
    const int mMyPlayerID;
    std::vector<class Player*> mPlayers;
    class Player* mPlayer;
    class Stage* mStage;
};