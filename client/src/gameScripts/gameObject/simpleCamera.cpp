#include "simpleCamera.h"
#include "../../../../common/src/component/transform.h"
#include "../../../../utils/src/math.h"
#include "../../component/camera.h"
#include "../../renderer.h"

SimpleCamera::SimpleCamera(Matrix4 projection, bool initialUse)
    : GameObject()
{
    Camera* camera = new Camera(this, projection);
    AddComponent(camera);
    if (initialUse)
        camera->Use();
}