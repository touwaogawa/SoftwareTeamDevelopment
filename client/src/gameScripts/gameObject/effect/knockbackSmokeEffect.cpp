#include "knockbackSmokeEffect.h"
#include "../../../../../common/src/component/transform.h"
#include "../../../component/billbourdRenderer.h"
#include "../../components/behaviour/effect/billbourdAnimationMove.h"
KnockbackSmokeEffect::KnockbackSmokeEffect(Vector3 pos)
    : GameObject("KnockbackSmokeEffect")
{
    BillbourdRenderer* br = new BillbourdRenderer(this, "../assets/textures/battleScene/smoke.png");
    // BillbourdRenderer* br = new BillbourdRenderer(this, "../assets/textures/humanColor_red.png");
    AddComponent(br);
    SetBehaviour(new BillbordAnimationMove(this, br, 2, 4, 2, 16));
    GetTransform()->SetWorldPosition(pos);
    GetTransform()->SetLocalScale(Vector3(1.0f, 1.0f, 1.0f) * 0.005f);
    // std::cout << "KnockbackSmokeEffect constructor" << std::endl;
}