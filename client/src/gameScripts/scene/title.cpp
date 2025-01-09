#include "title.h"
#include "../../../../common/src/sceneManager.h"
#include "../../../../utils/src/input.h"
#include "../gameObject/ui/title.h"
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
    new TitleUI(this, nullptr);
    return true;
}
void TitleScene::Update(bool& exitFrag, float timeStep)
{
    ProccessInput();
    Scene::Update(exitFrag, timeStep);
}

bool TitleScene::ProccessInput()
{
    if (Input::GetKeyDown(SDL_SCANCODE_RETURN)) {
        SceneManager::LoadScene(new MatchingScene());
    }
    return true;
}
