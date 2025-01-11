#include "title.h"
#include "../../../../common/src/sceneManager.h"
#include "../../../../utils/src/input.h"
#include "../components/behaviour/pressAnyButtonMove.h"
#include "../gameObject/player.h"
#include "../gameObject/stage.h"
#include "../gameObject/titleCamera.h"
#include "../gameObject/ui/simpleSprite.h"
#include "../gameObject/ui/titleUI.h"
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
    new Stage_C(this, nullptr);
    new TitleCamera(this, nullptr);
    PlayerInfo playerInfo(0, "name", RiderType::BaseHuman, BeyType::Hexagram);
    mPlayer     = new Player_C(this, playerInfo, &currentFrame);
    Matrix4 mat = Matrix4::CreateScale(Vector3(0.6f, 0.6f, 0.6f));
    mat *= Matrix4::CreateTranslation(Vector3(0.0f, -350.0f, 0.0f));
    SimpleSprite* ss = new SimpleSprite(this, nullptr, mat, "../assets/textures/PressAnyButton.png");
    ss->SetBehaviour(new PressAnyButtonMove(ss));
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
