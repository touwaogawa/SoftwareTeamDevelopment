#include "title.h"
#include "../../../common/src/sceneManager.h"
#include "../beySmashEngine.h"
#include "matching.h"
TitleScene::TitleScene()
    : Scene("TitleScene")
{
}

TitleScene::~TitleScene()
{
}

bool TitleScene::Load()
{
    return true;
}

void TitleScene::BeforeUpdateGameObject()
{
    ProccessInput();
}

void TitleScene::AfterUpdateGameObject()
{
}

bool TitleScene::ProccessInput()
{
    if (Input::GetKeyDown(SDL_SCANCODE_RETURN)) {
        SceneManager::LoadScene(new MatchingScene());
    }
    return true;
}
