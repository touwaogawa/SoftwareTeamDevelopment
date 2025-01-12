#include "title.h"
#include "../../../../common/src/sceneManager.h"
#include "../../../../utils/src/input.h"
#include "../../component/camera.h"
#include "../components/behaviour/pressAnyButtonMove.h"
#include "../components/behaviour/titleCameraMove.h"
#include "../gameObject/player.h"
#include "../gameObject/simpleCamera.h"
#include "../gameObject/simpleMeshModel.h"
#include "../gameObject/simpleSprite.h"
#include "../gameObject/stage.h"
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

    // ロゴ
    GameObject* titleui = new SimpleSprite("../assets/textures/title.png");
    Instantiate(titleui);

    // press any button
    GameObject* pressAnyButton = new SimpleSprite("../assets/textures/PressAnyButton.png");
    pressAnyButton->SetBehaviour(new PressAnyButtonMove(pressAnyButton));
    Matrix4 mat = Matrix4::CreateScale(Vector3(0.6f, 0.6f, 0.6f));
    mat *= Matrix4::CreateTranslation(Vector3(0.0f, -350.0f, 0.0f));
    Instantiate(pressAnyButton, mat);

    // camera
    // Matrix4 projection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(40.0f),
    //     Renderer::GetWindowWidth(),
    //     Renderer::GetWindowHeight(),
    //     0.1f,
    //     150.0f);
    GameObject* camera = new SimpleCamera();
    Camera* c          = camera->GetComponent<Camera>();
    c->Use();
    // std::cout << "aa" << std::endl;
    camera->SetBehaviour(new TitleCameraMove(camera));
    // std::cout << "aa" << std::endl;
    Instantiate(camera, mat);
    // std::cout << "aa" << std::endl;

    // stage
    GameObject* stage = new SimpleMeshModel("../assets/models/Stage.obj", "../assets/textures/simpleTile.png");
    Instantiate(stage);

    GameObject* colosseum = new SimpleMeshModel("../assets/models/colosseum.obj", "../assets/textures/sand.png");
    mat                   = Matrix4::CreateScale(Vector3(1.0f, 1.0f, 1.0f) * 4.0f);
    mat *= Matrix4::CreateTranslation(Vector3(0.0f, -40.0f, 0.0f));
    Instantiate(colosseum, mat);

    // std::cout << "aa" << std::endl;
    // PlayerInfo playerInfo(0, "name", RiderType::BaseHuman, BeyType::Hexagram);
    // mPlayer = new Player_C(this, playerInfo, &currentFrame);

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
