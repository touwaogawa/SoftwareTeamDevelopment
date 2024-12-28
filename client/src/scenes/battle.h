#pragma once
#include "../gameScripts/hero/hero.h"
#include "../scene.h"
#include <vector>

class BattleScene : public Scene {
public:
    BattleScene(int playerNum);
    ~BattleScene() override;
    bool Load() override;
    bool ProccessInput() override;

    class Stage* GetStage() const;

private:
    const int mPlayerNum;
    std::vector<class Player*> mPlayers;
    class Player* mPlayer;
    class Stage* mStage;
};