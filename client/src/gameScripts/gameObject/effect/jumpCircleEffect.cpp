#include "jumpCircleEffect.h"
#include "../../../../../common/src/component/transform.h"
#include "../../../component/meshRenderer.h"
#include "../../components/behaviour/effect/scalingMove.h"
JumpCircleEffect::JumpCircleEffect(Vector3 pos)
    : GameObject("JumpCircleEffect")
{
    AddComponent(new MeshRenderer(this, "../assets/models/square.obj", "../assets/textures/battleScene/circle.png", true));
    SetBehaviour(new ScalingMove(this, Vector3(1.1f, 1.0f, 1.1f), 9));
    GetTransform()->SetWorldPosition(pos);
    GetTransform()->SetLocalScale(Vector3(1.0f, 1.0f, 1.0f) * 0.5f);
}