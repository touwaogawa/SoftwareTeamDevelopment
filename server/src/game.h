#pragma once
class Game {
public:
    Game();
    bool Init();
    void RunLoop(int playerNum);
    void Shutdown();

private:
};