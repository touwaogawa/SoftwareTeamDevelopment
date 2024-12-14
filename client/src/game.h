#pragma once

class Game {
public:
    Game();
    bool Init();
    void RunLoop();
    void Shutdown();

private:
    class Scene* mCurrentScene;
    class BattleScene* mBattleScene;
};