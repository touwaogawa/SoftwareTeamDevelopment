#include "battle.h"
#include "../../../../common/src/component/transform.h"
#include "../../../../common/src/gameScripts/components/behaviour/beyMove.h"
#include "../../../../common/src/gameScripts/components/behaviour/heroMove.h"
#include "../../../../common/src/gameScripts/components/behaviour/playerMove.h"
#include "../../../../common/src/gameScripts/components/behaviour/riderMove.h"
#include "../../../../common/src/gameScripts/gameObject/bey.h"
#include "../../../../common/src/gameScripts/gameObject/hero.h"
#include "../../../../common/src/gameScripts/gameObject/player.h"
#include "../../../../common/src/gameScripts/gameObject/rider.h"
#include "../../../../common/src/gameScripts/gameObject/stage.h"
#include "../../../../common/src/gameScripts/packetData.h"
#include "../../../../common/src/sceneManager.h"
#include "../../../../utils/src/input.h"
#include <iostream>
#include <reactphysics3d/reactphysics3d.h>
#include <string>

BattleScene::BattleScene(int playerNum, std::vector<PlayerInfo> playerInfos)
    : Scene("BattleScene")
    , mPlayerNum(playerNum)
    , mPlayerInfos(playerInfos)
{
}

BattleScene::~BattleScene()
{
}
bool BattleScene::Load()
{

    // std::cout << "mPlayeyNum " << mPlayerNum << std::endl;
    for (int i = 0; i < mPlayerNum; i++) {
        std::string tag = "Player" + std::to_string(mPlayerInfos[i].id);
        // std::cout << "player gen " << mPlayerInfos[i].id << std::endl;
        // player
        Player* player = new Player(mPlayerInfos[i], tag);
        player->SetBehaviour(new PlayerMove(player));
        Instantiate(player);
        mPlayers.push_back(player);

        // hero
        Hero* hero = new Hero(player, mPlayerInfos[i].heroInfo, mPhysics, tag);
        hero->SetBehaviour(new HeroMove(hero));
        float r     = 13.0f;
        float x     = r * Math::Sin(Math::TwoPi / mPlayerNum * mPlayerInfos[i].id);
        float z     = r * Math::Cos(Math::TwoPi / mPlayerNum * mPlayerInfos[i].id);
        Matrix4 mat = Matrix4::CreateTranslation(Vector3(x, 0.0f, z));
        Instantiate(hero, mat, player->GetTransform());

        // bey
        Bey* bey = new Bey(hero, mPlayerInfos[i].heroInfo.beyType, tag);
        // std::cout << "3 " << std::endl;
        bey->SetBehaviour(new BeyMove(bey));
        // std::cout << "3 " << std::endl;
        Instantiate(bey, hero->GetTransform(), false);
        // std::cout << "player gen _" << i << std::endl;

        // std::cout << "2 " << std::endl;
        // rider
        Rider* rider = new Rider(hero, mPlayerInfos[i].heroInfo.riderType, tag);
        // std::cout << "2 " << std::endl;
        rider->SetBehaviour(new RiderMove(rider));
        // std::cout << "2 " << std::endl;
        Instantiate(rider, hero->GetTransform(), false);

        // std::cout << "3 " << std::endl;
    }

    mStage = new Stage(mPhysics, "../assets/models/stage.obj");
    Instantiate(mStage);
    // std::cout << "3 " << std::endl;
    return true;
}
void BattleScene::SetENet(ENetAddress address, ENetHost* server)
{
    mAddress = address;
    mServer  = server;
}
void BattleScene::Update(bool& exitFrag, float timeStep)
{
    // std::cout << "SendCurrentFram " << std::endl;
    SendCurrentFrame();
    // std::cout << "pro net " << std::endl;
    ProccessNetowork();
    // std::cout << "pro inp " << std::endl;
    ProccessInput();
    // std::cout << "upd" << std::endl;
    Scene::Update(exitFrag, timeStep);
    // std::cout << "send " << std::endl;
    SendCurrentBattleStatus();
    // std::cout << ".." << std::endl;

    if (mPlayerNum > 1) {
        int defeatplayer = 0;
        for (Player* player : mPlayers) {
            if (player->GetHero()->GetState() == HeroState::Death) {
                defeatplayer++;
            }
        }
        if (defeatplayer == mPlayerNum - 1) {
            PacketData packetData(PacketDataType::GameEnd);
            enet_host_broadcast(mServer, 0, packetData.CreatePacket());
            enet_host_flush(mServer);
        }
    }
}

int BattleScene::GetPlayerNum() const
{
    return mPlayerNum;
}
Stage* BattleScene::GetStage() const
{
    return mStage;
}

bool BattleScene::ProccessInput()
{
    if (Input::GetKeyDown(SDL_SCANCODE_ESCAPE)) {
        return false;
    }
    return true;
}
bool BattleScene::ProccessNetowork()
{
    switch (mBattleState) {
    case BattleState::CountDown:
        std::cout << "BattleScene ContDown" << std::endl;
        mBattleState = BattleState::Battle;
        break;
    case BattleState::Battle: {
        // std::cout << "BattleScene Battle" << std::endl;
        mENetEvent;
        while (enet_host_service(mServer, &mENetEvent, 0) > 0) {
            switch (mENetEvent.type) {
            case ENET_EVENT_TYPE_CONNECT:
                std::cout << "Connected to server!" << std::endl;
                break;
            case ENET_EVENT_TYPE_RECEIVE:
                // std::cout << "eetr" << std::endl;
                switch (PacketData::RecognizePacketDatatype(mENetEvent.packet)) {
                case PacketDataType::BattleCommand: {
                    // std::cout << "recv bcd" << std::endl;
                    BattleCommandData battleCommandData;
                    battleCommandData.LoadPacket(mENetEvent.packet);
                    // コマンド追加
                    mPlayers[battleCommandData.id]->commandBuffer.push_front(battleCommandData.commandData);
                    // コマンドを全員に送信
                    enet_host_broadcast(mServer, 0, battleCommandData.CreatePacket());
                    enet_host_flush(mServer);

                } break;
                default:
                    std::cout << "default data" << std::endl;
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
    default:
        break;
    }
    return true;
}

void BattleScene::SendCurrentFrame()
{
    CurrentFrameData currentFrameData;
    currentFrameData.currentFrame = currentFrame;
    enet_host_broadcast(mServer, 0, currentFrameData.CreatePacket());
}

void BattleScene::SendCurrentBattleStatus()
{
    for (int i = 0; i < mPlayerNum; i++) {
        PlayerCurrentData playerCurrentData;
        playerCurrentData.id                = mPlayers[i]->GetID();
        playerCurrentData.heroCurrentStatus = mPlayers[i]->GetHero()->mCurrentStatus;
        playerCurrentData.heroTransform     = mPlayers[i]->GetHero()->GetTransform()->GetWorldMatrix();
        ENetPacket* p                       = playerCurrentData.CreatePacket();
        enet_host_broadcast(mServer, 0, p);
    }
    enet_host_flush(mServer);
}