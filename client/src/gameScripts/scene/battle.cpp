#include "battle.h"
#include "../../../../common/src/component/transform.h"
#include "../../../../common/src/gameScripts/packetData.h"
#include "../../../../common/src/physics.h"
#include "../../../../common/src/sceneManager.h"
#include "../../../../utils/src/input.h"
#include "../../audio.h"
#include "../../component/cameraComponent.h"
#include "../../component/meshRenderer.h"
#include "../components/behaviour/battleCameraMove.h"
#include "../components/behaviour/beyMove.h"
#include "../components/behaviour/heroMove.h"
#include "../components/behaviour/playerMove.h"
#include "../components/behaviour/riderMove.h"
#include "../gameObject/bey.h"
#include "../gameObject/player.h"
#include "../gameObject/rider.h"
#include "../gameObject/simpleBillbourd.h"
#include "../gameObject/simpleCamera.h"
#include "../gameObject/simpleMeshModel.h"
#include "../gameObject/simplesprite.h"
#include "../gameObject/stage.h"
#include <enet/enet.h>
#include <iostream>
#include <string>

BattleScene::BattleScene(int myPlayerID, int playerNum, std::vector<PlayerInfo> playerInfos)
    : Scene("BattleScene")
    , mBattleState(BattleState::CountDown)
    , mPlayerNum(playerNum)
    , mMyPlayerID(myPlayerID)
    , mPlayerInfos(playerInfos)
{
}

BattleScene::~BattleScene()
{
}
bool BattleScene::Load()
{
    // camera
    GameObject* camera               = new SimpleCamera();
    CameraComponent* cameraComponent = camera->GetComponent<CameraComponent>();
    cameraComponent->Use();
    BattleCameraMove* bcm = new BattleCameraMove(camera);
    camera->SetBehaviour(bcm);
    Vector3 cameraPos = Vector3(0.0f, 40.0f, -40.f);
    Matrix4 mat       = Matrix4::CreateLookAt(cameraPos, Vector3(0.0f, 2.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
    Instantiate(camera, mat);

    // std::cerr << "playerNum: " << mPlayerNum << std::endl;
    for (int i = 0; i < mPlayerNum; i++) {
        std::string tag = "Player" + std::to_string(mPlayerInfos[i].id);
        // player
        // std::cout << "i " << i << std::endl;
        // std::cout << "playerid " << mPlayerInfos[i].id << std::endl;
        Player* player = new Player(mPlayerInfos[i], tag);
        player->SetBehaviour(new PlayerMove_C(player));
        Instantiate(player);
        mPlayers.push_back(player);

        // hero
        Hero* hero = new Hero(player, mPlayerInfos[i].heroInfo, mPhysics, tag);
        hero->SetBehaviour(new HeroMove_C(hero));
        float r = 13.0f;
        float x = r * Math::Sin(Math::TwoPi / mPlayerNum * mPlayerInfos[i].id);
        float z = r * Math::Cos(Math::TwoPi / mPlayerNum * mPlayerInfos[i].id);
        mat     = Matrix4::CreateTranslation(Vector3(x, 0.0f, z));
        Instantiate(hero, mat, player->GetTransform());

        // player name
        std::string namefile = "../assets/textures/battleScene/player" + std::to_string(mPlayerInfos[i].id + 1) + ".png";
        GameObject* bill     = new SimpleBillbourd(namefile);
        Matrix4 mat4         = Matrix4::CreateScale(Vector3(1.0f, 1.0f, 1.0f) * 0.01f);
        mat4 *= Matrix4::CreateTranslation(Vector3(0.0f, 4.0f, 0.0f));
        bill->GetTransform()->SetLocalMatrix(mat4);
        Instantiate(bill, hero->GetTransform(), false);

        // camera
        bcm->AddHero(hero);

        // rider
        Rider_C* rider = new Rider_C(hero, mPlayerInfos[i].heroInfo.riderType, tag);
        rider->SetBehaviour(new RiderMove_C(rider));
        Instantiate(rider, hero->GetTransform(), false);
        // bey
        Bey_C* bey = new Bey_C(hero, mPlayerInfos[i].heroInfo.beyType, tag);
        bey->SetBehaviour(new BeyMove_C(bey));
        Instantiate(bey, hero->GetTransform(), false);
    }
    mPlayer = mPlayers[mMyPlayerID];

    mStage = new Stage_C(mPhysics, "../assets/models/Stage.obj", "../assets/textures/simpleTile.png");
    Instantiate(mStage);

    // colosseum
    GameObject* colosseum = new SimpleMeshModel("../assets/models/colosseum.obj", "../assets/textures/sand.png");
    mat                   = Matrix4::CreateScale(Vector3(1.0f, 1.0f, 1.0f) * 4.0f);
    mat *= Matrix4::CreateTranslation(Vector3(0.0f, -40.0f, 0.0f));
    Instantiate(colosseum, mat);

    return true;
}

void BattleScene::SetENet(ENetAddress address, ENetHost* client, ENetPeer* peer)
{
    mAddress = address;
    mClient  = client;
    mPeer    = peer;
}
void BattleScene::Update(bool& exitFrag, float timeStep)
{
    std::cout << "1" << std::endl;
    ProccessNetowork();
    std::cout << "2" << std::endl;

    // Transformをdynamic objectのrp3d::Transformに反映
    mPhysics->SetDynamicTransform();
    std::cout << "3" << std::endl;
    ProccessInput();
    std::cout << "4" << std::endl;
    Scene::Update(exitFrag, timeStep);
    std::cout << "5" << std::endl;
}

Stage* BattleScene::GetStage() const
{
    return mStage;
}

int BattleScene::GetPlayerNum() const
{
    return mPlayerNum;
}

bool BattleScene::ProccessInput()
{
    switch (mBattleState) {
    case BattleState::CountDown: {

    } break;
    case BattleState::Battle: {
        CommandData commandData = {
            Input::GetButton(2),
            Input::GetButton(3),
            Input::GetButton(1) || Input::GetButton(4),
            Vector2(Input::GetAxis(1), -Input::GetAxis(2)),
            Vector2(Input::GetAxis(3), -Input::GetAxis(4)),
            currentFrame
        };
        mPlayer->commandBuffer.push_front(commandData);

        // 送信
        BattleCommandData bcd;
        bcd.id             = mMyPlayerID;
        bcd.commandData    = commandData;
        ENetPacket* packet = bcd.CreatePacket();
        if (enet_peer_send(mPeer, 0, packet) < 0) {
            std::cerr << "Failed to send packet!!" << std::endl;
        }
    } break;
    default:
        std::cout << "battle state error" << std::endl;
        break;
    }
    return true;
}

bool BattleScene::ProccessNetowork()
{
    switch (mBattleState) {
    case BattleState::CountDown:
        // std::cout << "BattleScene ContDown" << std::endl;
        std::cout << "my Id " << mMyPlayerID << std::endl;
        Audio::SetMusicVolume(0.25);
        Audio::PlayMusic("../assets/sounds/bgm/Comet_Trails.mp3");
        mBattleState = BattleState::Battle;
        break;
    case BattleState::Battle: {
        // std::cout << "battle state battle" << std::endl;
        mENetEvent;
        while (enet_host_service(mClient, &mENetEvent, 0) > 0) {
            switch (mENetEvent.type) {
            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "Connected to server!" << std::endl;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                switch (PacketData::RecognizePacketDatatype(mENetEvent.packet)) {
                case PacketDataType::CurrentFrame: {
                    CurrentFrameData currentFrameData;
                    currentFrameData.LoadPacket(mENetEvent.packet);
                    // サーバーのフレームと同じフレームに更新
                    currentFrame = currentFrameData.currentFrame;
                } break;
                case PacketDataType::BattleCommand: {
                    // std::cout << "recv command" << std::endl;
                    BattleCommandData battleCommandData;
                    battleCommandData.LoadPacket(mENetEvent.packet);
                    // std::cout << battleCommandData.id << std::endl;
                    // std::cout << mMyPlayerID << std::endl;
                    // コマンド追加
                    if (battleCommandData.id != mMyPlayerID)
                        mPlayers[battleCommandData.id]->commandBuffer.push_front(battleCommandData.commandData);
                } break;
                case PacketDataType::PlayerCurrentData: {
                    // PlayerCurrentData playerCurrentData;
                    // playerCurrentData.LoadPacket(mENetEvent.packet);
                    // int id                                  = playerCurrentData.id;
                    // mPlayers[id]->GetHero()->mCurrentStatus = playerCurrentData.heroCurrentStatus;
                    // mPlayers[id]->GetHero()->GetTransform()->SetWorldMatrix(playerCurrentData.heroTransform);
                } break;
                case PacketDataType::GameEnd: {
                    Audio::PlayMusic("../assets/sounds/bgm/ピエロは暗闇で踊る.mp3");
                    Audio::PlayChunk("../assets/sounds/se/歓声と拍手1.mp3");
                    SimpleSprite* ss = new SimpleSprite("../assets/textures/gameend.png");
                    Instantiate(ss);
                } break;
                default:
                    std::cout << "PacketData error" << std::endl;
                    break;
                }
                enet_packet_destroy(mENetEvent.packet); // パケットの解放
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << "Disconnected from server." << std::endl;
                return false;
            default:
                break;
            }
        }
        // enet_host_flush(mClient);
    } break;
    default:
        break;
    }
    return true;
}
