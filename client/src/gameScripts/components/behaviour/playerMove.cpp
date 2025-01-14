#include "playerMove.h"
#include "../../../audio.h"

PlayerMove_C::PlayerMove_C(Player* owner)
    : PlayerMove(owner)
{
}

void PlayerMove_C::DefeatedAction1()
{
    Audio::PlayChunk("../assets/sounds/se/大勢で拍手.mp3");
}
void PlayerMove_C::DefeatedAction2()
{
    Audio::PlayChunk("../assets/sounds/se/ニワトリの鳴き声1.mp3");
}
void PlayerMove_C::DefeatedAction3Normal()
{
    Audio::PlayChunk("../assets/sounds/se/時代劇演出1.mp3");
}
void PlayerMove_C::DefeatedAction3Special()
{
    Audio::PlayChunk("../assets/sounds/se/カラスが鳴く夕方.mp3");
}