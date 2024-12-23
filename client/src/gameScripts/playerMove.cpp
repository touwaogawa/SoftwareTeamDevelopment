#include "playerMove.h"
#include "../beySmashEngine.h"
#include "../scenes/battle.h"
#include "player.h"

PlayerMove::PlayerMove(GameObject* owner)
    : Behaviour(owner)
{
}

void PlayerMove::Start()
{
}
namespace {

}
void PlayerMove::Update()
{
    // オーナーのオブジェクトをPlayerクラスとして代入
    Player* player           = static_cast<Player*>(GetOwner());
    BattleScene* battleScene = static_cast<BattleScene*>(GetOwner()->GetScene());

    if (!player->commandBuffer.empty()) {
        CommandData commandData = player->commandBuffer.back();
        // コマンドバッファが空でないとき
        int commandDelay = 1;
        while (commandData.inputFrame <= battleScene->currentFrame - commandDelay) {
            // commandDelayフレームより過去のコマンドを実行
            switch (commandData.commandType) {
            case CommandType::Attack:
                std::cout << "attak!" << std::endl;
                break;
            case CommandType::Charge:
                std::cout << "charge!" << std::endl;
                break;
            case CommandType::Jump:
                std::cout << "jump!" << std::endl;
                break;
            case CommandType::Dash:
                Hero* hero = static_cast<Hero*>(player->GetHero());
                hero->std::cout << "move!" << std::endl;
                break;
            default:
                std::cout << "command type error" << std::endl;
                break;
            }
            // コマンドバッファからコマンド削除
            player->commandBuffer.pop_back();
            if (player->commandBuffer.empty()) {
                // コマンドバッファが空になったら修了
                break;
            }
        }
    } else {
        // コマンドバッファが空のとき
    }
}
void PlayerMove::LateUpdate()
{
}
