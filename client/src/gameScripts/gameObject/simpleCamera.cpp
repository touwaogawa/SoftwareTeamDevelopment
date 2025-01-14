#include "simpleCamera.h"
#include "../../../../common/src/component/transform.h"
#include "../../../../utils/src/math.h"
#include "../../component/cameraComponent.h"
#include "../../renderer.h"

SimpleCamera::SimpleCamera(Matrix4 projection, bool initialUse)
    : GameObject()
{
    CameraComponent* cameraComponent = new CameraComponent(this, projection);
    AddComponent(cameraComponent);
    if (initialUse)
        cameraComponent->Use();
}