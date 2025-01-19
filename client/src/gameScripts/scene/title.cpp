#include "title.h"
#include "../../../../common/src/component/transform.h"
#include "../../../../common/src/sceneManager.h"
#include "../../../../utils/src/input.h"
#include "../../component/cameraComponent.h"
#include "../components/behaviour/pressAnyButtonMove.h"
#include "../components/behaviour/titleCameraMove.h"
#include "../gameObject/player.h"
#include "../gameObject/simpleBillbourd.h"
#include "../gameObject/simpleCamera.h"
#include "../gameObject/simpleEffect.h"
#include "../gameObject/simpleMeshModel.h"
#include "../gameObject/simpleSprite.h"
#include "../gameObject/stage.h"
#include "matching.h"
TitleScene::TitleScene()
    : Scene("TitleScene")
{
}

bool TitleScene::Load()
{

    // camera
    SimpleCamera* camera = new SimpleCamera();
    CameraComponent* c   = camera->GetComponent<CameraComponent>();
    c->Use();
    // std::cout << "aa" << std::endl;
    camera->SetBehaviour(new TitleCameraMove(camera, c));
    // std::cout << "aa" << std::endl;

    // ロゴ
    // SimpleSprite* titleui =
    new SimpleSprite("../assets/textures/titleScene/title.png");

    // press any button
    SimpleSprite* pressAnyButton = new SimpleSprite("../assets/textures/titleScene/PressAnyButton.png");

    pressAnyButton->SetBehaviour(new PressAnyButtonMove(pressAnyButton));
    pressAnyButton->GetTransform()->SetWorldScale(Vector3(0.6f, 0.6f, 0.6f));
    pressAnyButton->GetTransform()->SetWorldPosition(Vector3(0.0f, -350.0f, 0.0f));

    // stage
    // SimpleMeshModel* stage =
    new Stage(mPhysics, "../assets/models/Stage.obj", "../assets/textures/simpleTile.png");

    // colosseum
    SimpleMeshModel* colosseum = new SimpleMeshModel("../assets/models/colosseum.obj", "../assets/textures/sand.png");
    colosseum->GetTransform()->SetWorldScale(Vector3(1.0f, 1.0f, 1.0f) * 4.0f);
    colosseum->GetTransform()->SetWorldPosition(Vector3(0.0f, -40.0f, 0.0f));

    // effect
    // GameObject* effect = new SimpleEffect("../assets/models/square.obj", "../assets/textures/silver.png");
    // Matrix4 mat3       = Matrix4::CreateTranslation(Vector3(7.0f, 9.0f, 0.0f));
    // // mat3 *= Matrix4::CreateRotationX(90.0f);
    // Instantiate(effect, mat3);

    // billbourd
    // GameObject* bill = new SimpleBillbourd("../assets/textures/player2.png");

    // Matrix4 mat4 = Matrix4::CreateScale(Vector3(1.0f, 1.0f, 1.0f) * 0.01f);
    // mat4 *= Matrix4::CreateTranslation(Vector3(7.0f, 10.0f, 0.0f));
    // Instantiate(bill, mat4);

    // std::cout << "aa" << std::endl;
    PlayerInfo playerInfo(-1, "name", RiderType::BaseHuman, BeyType::Hexagram);
    new Player(playerInfo, "title");

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
