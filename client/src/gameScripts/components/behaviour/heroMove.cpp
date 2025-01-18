#include "heroMove.h"
#include "../../../audio.h"
#include "../../../renderer.h"

HeroMove_C::HeroMove_C(Hero* owner)
    : HeroMove(owner)
{
}

void HeroMove_C::OnDamage(int stopFrame, int downFrame, rp3d::Vector3 vector)
{
    HeroMove::OnDamage(stopFrame, downFrame, vector);
    Audio::PlayChunk("../assets/sounds/se/軽いキック1.mp3");
}
void HeroMove_C::HitOther(int stopFrame, float power)
{
    HeroMove::HitOther(stopFrame, power);
    Renderer::CameraShakeStart(stopFrame / 2, power);
}
