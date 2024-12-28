#include "title.h"
#include "../beySmashEngine.h"
#include "../sceneManager.h"
#include "battle.h"
TitleScene::TitleScene()
    : Scene("TitleScene")
{
}
TitleScene::~TitleScene()
{
}
bool TitleScene::Load()
{
    if (!mRenderer->Load()) {
        std::cout << "Failed Renderer Load" << std::endl;
        return false;
    }
    return true;
}

bool TitleScene::ProccessInput()
{
    if (Input::GetKeyDown(SDL_SCANCODE_RETURN)) {
        int playerNum = 4;
        SceneManager::LoadScene(new BattleScene(0, playerNum));
    }
    return true;
}
