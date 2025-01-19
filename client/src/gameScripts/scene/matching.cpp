#include "matching.h"
#include "../../../../common/src/component/transform.h"
#include "../../../../common/src/gameScripts/packetData.h"
#include "../../../../common/src/physics.h"
#include "../../../../common/src/sceneManager.h"
#include "../../../../utils/src/input.h"
#include "../../component/cameraComponent.h"
#include "../../renderer.h"
#include "../components/behaviour/beyMove.h"
#include "../components/behaviour/heroMove.h"
#include "../components/behaviour/playerMove.h"
#include "../components/behaviour/riderMove.h"
#include "../gameObject/player.h"
#include "../gameObject/rider.h"
#include "../gameObject/simpleCamera.h"
#include "../gameObject/simpleMeshModel.h"
#include "../gameObject/simpleSprite.h"
#include "../gameObject/stage.h"
#include "battle.h"
#include <enet/enet.h>
#include <iostream>
#include <queue>
#include <utility>

MatchingScene::MatchingScene()
    : Scene("MatchingScene")
    , mMatchingState(MatchingState::Init)
    , mConnectingSprite(nullptr)
    , mMatchingSprite(nullptr)
    , mPreStartSprite(nullptr)
    , mStartCount(0)
{
}

bool MatchingScene::Load()
{
    // camera
    SimpleCamera* camera             = new SimpleCamera();
    CameraComponent* cameraComponent = camera->GetComponent<CameraComponent>();
    cameraComponent->Use();
    camera->GetTransform()->SetWorldPosition(Vector3(0.0f, 5.0f, -20.f));

    // stage
    // Stage_C* stage =
    new Stage(mPhysics, "../assets/models/Stage.obj", "../assets/textures/simpleTile.png");

    // colosseum
    GameObject* colosseum = new SimpleMeshModel("../assets/models/colosseum.obj", "../assets/textures/sand.png");
    colosseum->GetTransform()->SetWorldScale(Vector3(1.0f, 1.0f, 1.0f) * 4.0f);
    colosseum->GetTransform()->SetWorldPosition(Vector3(0.0f, -40.0f, 0.0f));

    // Player##########################################################

    PlayerInfo playerInfo(0, "aa", RiderType::BaseHuman, BeyType::Shuriken);
    std::string tag = "Player";
    // player
    mPlayer = new Player(playerInfo, tag);
    mPlayer->GetHero()->GetTransform()->SetWorldPosition(Vector3(5.0f, 0.0f, 0.0f));

    // ##########################################################

    // 接続中の文字
    mConnectingSprite = new SimpleSprite("../assets/textures/matchingScene/connectingServer.png");
    mConnectingSprite->GetTransform()->SetWorldScale(Vector3(1.0f, 1.0f, 1.0f) * 0.6f);
    mConnectingSprite->GetTransform()->SetWorldPosition(Vector3(0.0f, -350.0f, 0.0f));

    std::cout << "loaded" << std::endl;
    return true;
}
void MatchingScene::Update(bool& exitFrag, float timeStep)
{
    ProccessNetowork();
    // std::cout << "after proccessNetwork" << std::endl;
    ProccessInput();
    // std::cout << "after proccessInput" << std::endl;
    // std::cout << "rgonum : " << mRootObjects.size() << std::endl;
    Scene::Update(exitFrag, timeStep);
}

bool MatchingScene::ProccessInput()
{
    if (Input::GetKeyUp(SDL_SCANCODE_ESCAPE)) {
        return false;
    }

    // std::cout << "input" << std::endl;

    switch (mMatchingState) {
    case MatchingState::Init:

    case MatchingState::Connecting:
    case MatchingState::Connected: {
        // CommandData commandData = {
        //     Input::GetButton(2),
        //     Input::GetButton(3),
        //     Input::GetButton(1) || Input::GetButton(4),
        //     Vector2(Input::GetAxis(1), -Input::GetAxis(2)),
        //     Vector2(Input::GetAxis(3), -Input::GetAxis(4)),
        //     currentFrame
        // };
        // mPlayer->SetCommandData(commandData);
    } break;
    case MatchingState::StartBattle: {
    } break;
    default:
        std::cout << "MatchingState error" << std::endl;
        break;
    }

    return true;
}

bool MatchingScene::ProccessNetowork()
{
    // std::cout << "pn" << std::endl;
    switch (mMatchingState) {
    case MatchingState::Init:
        mClient = enet_host_create(
            NULL,        // IPアドレスは自動選択
            1,           // 1接続のみ
            2,           // チャネル数
            57600, 14400 // 最大送受信帯域幅
        );

        if (mClient == NULL) {
            std::cerr << "Failed to create ENet client!" << std::endl;
            return false;
        }

        // サーバーのアドレス設定
        enet_address_set_host(&mAddress, "127.0.0.1"); // サーバーのIPアドレス
        mAddress.port = 1234;

        // サーバーに接続
        mPeer = enet_host_connect(mClient, &mAddress, 2, 0);
        if (mPeer == NULL) {
            std::cerr << "No available peers for initiating an connection!" << std::endl;
            return false;
        }
        std::cout << "Connecting to server..." << std::endl;
        mMatchingState = MatchingState::Connecting;
        break;
    case MatchingState::Connecting: {
        // std::cout << "Connecting" << std::endl;
        while (enet_host_service(mClient, &mENetEvent, 0) > 0) {
            switch (mENetEvent.type) {
            case ENET_EVENT_TYPE_CONNECT: {
                std::cout << "Connected to server!" << std::endl;
                mConnectingSprite->Destroy();
                // マッチング中
                mMatchingSprite = new SimpleSprite("../assets/textures/matchingScene/matching.png");
                mMatchingSprite->GetTransform()->SetWorldScale(Vector3(1.0f, 1.0f, 1.0f) * 0.6f);
                mMatchingSprite->GetTransform()->SetWorldPosition(Vector3(0.0f, -350.0f, 0.0f));

                mMatchingState = MatchingState::Connected;
            } break;
            case ENET_EVENT_TYPE_RECEIVE:
                std::cout << "recv" << std::endl;
                // std::cout << "Received message from server: " << (char*)event.packet->data << std::endl;
                enet_packet_destroy(mENetEvent.packet); // パケットの解放
                break;
            case ENET_EVENT_TYPE_DISCONNECT:
                std::cout << "Disconnected from server." << std::endl;
                return false;
            default:
                break;
            }
        }
        // std::cout << "Connecting" << std::endl;
    } break;
    case MatchingState::Connected: {
        // std::cout << "Connected" << std::endl;
        while (enet_host_service(mClient, &mENetEvent, 0) > 0) {
            switch (mENetEvent.type) {
            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "Connected to server!" << std::endl;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                switch (PacketData::RecognizePacketDatatype(mENetEvent.packet)) {
                case PacketDataType::MatchingInit: {
                    IDInitData idInitData;
                    idInitData.LoadPacket(mENetEvent.packet);
                    myPlayerId = idInitData.id;
                    std::cout << "idInitData.id" << myPlayerId << std::endl;
                    // プレイヤーの情報仮
                    PlayerInfo playerInfo(myPlayerId, "name", RiderType::BaseHuman, BeyType::Shuriken);

                    PlayerInfoData playerInfoData;
                    playerInfoData.playerInfo = playerInfo;
                    ENetPacket* packet        = playerInfoData.CreatePacket();
                    if (enet_peer_send(mPeer, 0, packet) < 0) {
                        std::cerr << "Failed to send packet!" << std::endl;
                    }

                } break;
                case PacketDataType::PlayerInfo: {
                    PlayerInfoData playerInfoData;
                    playerInfoData.LoadPacket(mENetEvent.packet);
                    int id = playerInfoData.playerInfo.id;
                    std::cout << "recv data id : " << id << std::endl;
                    mPlayerInfos.push_back(playerInfoData.playerInfo);

                } break;
                case PacketDataType::StartBattle: {
                    std::cout << "start battle" << std::endl;
                    mMatchingSprite->Destroy();
                    StartBattleData startBattleData;
                    startBattleData.LoadPacket(mENetEvent.packet);
                    mStartCount = startBattleData.coutDownFrame;

                    mPreStartSprite = new SimpleSprite("../assets/textures/matchingScene/preStart.png");
                    mPreStartSprite->GetTransform()->SetWorldScale(Vector3(1.0f, 1.0f, 1.0f) * 0.6f);
                    mPreStartSprite->GetTransform()->SetWorldPosition(Vector3(0.0f, -350.0f, 0.0f));

                    mMatchingState = MatchingState::StartBattle;

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
    } break;
    case MatchingState::StartBattle: {
        if (mStartCount) {
            mStartCount--;
        } else {
            // std::cout << "pre load scene" << std::endl;
            BattleScene* battleScene = new BattleScene(myPlayerId, mPlayerInfos.size(), mPlayerInfos);
            battleScene->SetENet(mAddress, mClient, mPeer);
            SceneManager::LoadScene(battleScene);
            // std::cout << "loaded scene" << std::endl;
        }

    } break;
    default:
        std::cout << "MatchingState error" << std::endl;
        break;
    }

    return true;
}