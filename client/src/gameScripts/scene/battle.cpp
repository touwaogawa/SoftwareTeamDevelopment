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
#include "../components/behaviour/battleColosseumMove.h"
#include "../components/behaviour/battleStartMove.h"
#include "../components/behaviour/effect/faceDirMove.h"
#include "../components/behaviour/playerMove.h"
#include "../gameObject/player.h"
#include "../gameObject/playerUI.h"
#include "../gameObject/safeArea.h"
#include "../gameObject/simpleBillbourd.h"
#include "../gameObject/simpleCamera.h"
#include "../gameObject/simpleEffect.h"
#include "../gameObject/simpleMeshModel.h"
#include "../gameObject/simpleSprite.h"
#include "../gameObject/stage.h"
#include <enet/enet.h>
#include <iostream>
#include <string>

BattleScene::BattleScene(int myPlayerID, int playerNum, std::vector<PlayerInfo> playerInfos)
    : Scene("BattleScene")
    , mBattleState(BattleState::CountDown)
    , mNextBattleState(BattleState::CountDown)
    , mPlayerNum(playerNum)
    , mConnectPlayerNum(playerNum)
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
    SimpleCamera* camera             = new SimpleCamera();
    CameraComponent* cameraComponent = camera->GetComponent<CameraComponent>();
    cameraComponent->Use();
    camera->GetTransform()->SetWorldPosition(Vector3(0.0f, 40.0f, -40.f));
    BattleCameraMove* bcm = new BattleCameraMove(camera);
    camera->SetBehaviour(bcm);

    // safe area
    new SafeArea();

    // std::cerr << "playerNum: " << mPlayerNum << std::endl;
    for (int i = 0; i < mPlayerNum; i++) {
        std::string tag = "Player" + std::to_string(mPlayerInfos[i].id);
        // player
        // std::cout << "i " << i << std::endl;
        // std::cout << "playerid " << mPlayerInfos[i].id << std::endl;
        Player* player = new Player(mPlayerInfos[i], tag);
        mPlayers.push_back(player);

        Hero* hero = player->GetHero();
        Vector3 heroPos;
        float r = 13.0f;
        switch (mPlayerNum) {
        case 1: {
            heroPos = Vector3(0.0f, 0.0f, 0.0f);
        } break;
        case 2: {

            float x = r * Math::Cos(Math::TwoPi / mPlayerNum * mPlayerInfos[i].id + Math::Pi);
            float z = r * Math::Sin(Math::TwoPi / mPlayerNum * mPlayerInfos[i].id + Math::Pi);
            heroPos = Vector3(x, 0.0f, z);
        } break;
        case 3: {
            float x = r * Math::Cos(Math::TwoPi / mPlayerNum * mPlayerInfos[i].id + Math::PiOver2);
            float z = r * Math::Sin(Math::TwoPi / mPlayerNum * mPlayerInfos[i].id + Math::PiOver2);
            heroPos = Vector3(x, 0.0f, z);

        } break;
        case 4: {
            float x = r * Math::Cos(Math::TwoPi / mPlayerNum * mPlayerInfos[i].id + (Math::Pi + Math::PiOver2) * 0.5f);
            float z = r * Math::Sin(Math::TwoPi / mPlayerNum * mPlayerInfos[i].id + (Math::Pi + Math::PiOver2) * 0.5f);
            heroPos = Vector3(x, 0.0f, z);

        } break;
        default: {
            float x = r * Math::Cos(Math::TwoPi / mPlayerNum * mPlayerInfos[i].id - Math::PiOver2);
            float z = r * Math::Sin(Math::TwoPi / mPlayerNum * mPlayerInfos[i].id - Math::PiOver2);
            heroPos = Vector3(x, 0.0f, z);

        } break;
        }
        hero->GetTransform()->SetWorldPosition(heroPos);

        // player name
        std::string namefile       = "../assets/textures/battleScene/player" + std::to_string(mPlayerInfos[i].id + 1) + ".png";
        SimpleBillbourd* billbourd = new SimpleBillbourd(namefile);
        billbourd->GetTransform()->SetLocalScale(Vector3(1.0f, 1.0f, 1.0f) * 0.005f);
        billbourd->GetTransform()->SetLocalPosition(Vector3(0.0f, 4.0f, 0.0f));
        billbourd->GetTransform()->SetParent(hero->GetTransform(), false);

        // camera
        bcm->AddHero(hero);

        // playerUi
        PlayerUI* playerUI = new PlayerUI(mPlayerInfos[i].id);
        float width        = 300.0f + 240.0f / mPlayerNum;
        float uipos_x      = -(width * (mPlayerNum - 1) * 0.5f) + (width * mPlayerInfos[i].id);
        float uipos_y      = Renderer::GetWindowHeight() / 2.0f - 100.0f;
        playerUI->GetTransform()->SetWorldScale(Vector3(1.0f, 1.0f, 1.0f) * 0.2f);
        playerUI->GetTransform()->SetWorldPosition(Vector3(uipos_x, uipos_y, 0.0f));
    }
    // my player
    mPlayer = mPlayers[mMyPlayerID];

    // face dir
    SimpleEffect* faceDir = new SimpleEffect("../assets/models/square.obj", "../assets/textures/battleScene/faceDir.png");
    faceDir->SetBehaviour(new FaceDirMove(faceDir, mPlayer->GetHero()));
    faceDir->GetTransform()->SetLocalPosition(Vector3(0.0f, 0.1f, 0.0f));
    faceDir->GetTransform()->SetParent(mPlayer->GetHero()->GetTransform(), false);

    // stage
    mStage = new Stage(mPhysics, "../assets/models/Stage.obj", "../assets/textures/simpleTile.png");

    // colosseum
    SimpleMeshModel* colosseum = new SimpleMeshModel("../assets/models/colosseum.obj", "../assets/textures/sand.png");
    colosseum->GetTransform()->SetWorldScale(Vector3(1.0f, 1.0f, 1.0f) * 4.0f);
    colosseum->GetTransform()->SetWorldPosition(Vector3(0.0f, -40.0f, 0.0f));
    colosseum->SetBehaviour(new BattleColosseumMove(colosseum));

    mPhysics->SetDynamicTransform();

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
    mBattleState = mNextBattleState;
    ProccessNetowork();
    ProccessInput();
    switch (mBattleState) {
    case BattleState::CountDown: {
        if (currentFrame == 0) {
            Renderer::CameraShakeStart(60 * 4, 0.1f);
        }
        if (currentFrame == 60 * 4 + 50) {
            SimpleSprite* startBattle = new SimpleSprite("../assets/textures/battleScene/letsGo.png");
            startBattle->SetBehaviour(new BattleStartMove(startBattle));
            Audio::PlayChunk("../assets/sounds/se/火炎魔法3.mp3");
        }
        if (currentFrame == 60 * 5) {
            Audio::SetMusicVolume(0.25);
            Audio::PlayMusic("../assets/sounds/bgm/Comet_Trails.mp3");
            SetNextBattleState(BattleState::Battle);
        }
        Scene::Update(exitFrag, timeStep);
    } break;
    case BattleState::Battle: {
        while (true) {
            bool allCommand = true;
            bool allNothing = true;
            for (int i = 0; i < mConnectPlayerNum; i++) {
                if (mPlayerCommands[i].begin()->second.frame != currentFrame) {
                    allCommand = false;
                } else {
                    allNothing = false;
                }
            }
            if (allCommand) {
                for (int i = 0; i < mConnectPlayerNum; i++) {
                    mPlayers[i]->SetCommandData(mPlayerCommands[i].begin()->second);
                    mPlayerCommands[i].erase(mPlayerCommands[i].begin());
                }
                Scene::Update(exitFrag, timeStep);
                break;
            } else if (allNothing) {
                break;
            } else {
                ProccessNetowork();
            }
        }

    } break;
    case BattleState::Result: {
        Scene::Update(exitFrag, timeStep);

    } break;
    default:
        std::cout << "battle state error" << std::endl;
        break;
    }
    int alivePlayerNum = mPlayerNum;
    for (Player* player : mPlayers) {
        if (player->GetPlayerState() == PlayerState::Defeat) {
            alivePlayerNum--;
        }
    }
    if (mPlayerNum > 1) {
        if (alivePlayerNum <= 1) {
            Audio::PlayMusic("../assets/sounds/bgm/ピエロは暗闇で踊る.mp3");
            Audio::PlayChunk("../assets/sounds/se/歓声と拍手1.mp3");
            // SimpleSprite* ss =
            new SimpleSprite("../assets/textures/gameend.png");
            SetNextBattleState(BattleState::Result);
        }
    } else {
        if (alivePlayerNum <= 0) {
            Audio::PlayMusic("../assets/sounds/bgm/ピエロは暗闇で踊る.mp3");
            Audio::PlayChunk("../assets/sounds/se/歓声と拍手1.mp3");
            // SimpleSprite* ss =
            new SimpleSprite("../assets/textures/gameend.png");
            SetNextBattleState(BattleState::Result);
        }
    }
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
            currentFrame + 1
        };
        // mPlayerCommandsBuffer[commandData.frame][mMyPlayerID] = commandData;
        mPlayerCommands[mMyPlayerID][commandData.frame] = commandData;
        // mPlayerCommands[mMyPlayerID]                    = commandData;
        // 送信
        BattleCommandData bcd;
        bcd.id             = mMyPlayerID;
        bcd.commandData    = commandData;
        ENetPacket* packet = bcd.CreatePacket();
        if (enet_peer_send(mPeer, 0, packet) < 0) {
            std::cerr << "Failed to send packet!!" << std::endl;
        }
    } break;
    case BattleState::Result: {

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
        // std::cout << "my Id " << mMyPlayerID << std::endl;

        break;
    case BattleState::Battle: {
        // std::cout << "battle state battle" << std::endl;
        while (enet_host_service(mClient, &mENetEvent, 0) > 0) {
            switch (mENetEvent.type) {
            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "Connected to server!" << std::endl;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                switch (PacketData::RecognizePacketDatatype(mENetEvent.packet)) {
                case PacketDataType::BattleCommand: {
                    // std::cout << "recv battle command" << std::endl;
                    BattleCommandData battleCommandData;
                    battleCommandData.LoadPacket(mENetEvent.packet);
                    // std::cout << battleCommandData.id << std::endl;
                    // std::cout << mMyPlayerID << std::endl;

                    // コマンドバッファに追加
                    if (battleCommandData.id != mMyPlayerID)
                        mPlayerCommands[battleCommandData.id][battleCommandData.commandData.frame] = battleCommandData.commandData;
                } break;
                case PacketDataType::PlayerDisConnected: {
                    mConnectPlayerNum--;
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
    case BattleState::Result: {

    } break;
    default:
        break;
    }
    return true;
}
