#pragma once
#include "../../../common/src/gameScripts/hero/hero.h"
#include "../../../common/src/scene.h"
#include <vector>

class BattleScene : public Scene {
public:
    BattleScene(int playerNum);
    ~BattleScene() override;
    bool Load() override;

    class Stage* GetStage() const;
    int GetPlayerNum() const;

private:
    const int mPlayerNum;
    std::vector<class Player*> mPlayers;
    class Stage* mStage;
    void BeforeUpdateGameObject() override;
    void AfterUpdateGameObject() override;
    bool ProccessInput();
    void ProccessNetowork();
};