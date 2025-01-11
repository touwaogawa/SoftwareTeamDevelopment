#include "titleCamera.h"
#include "../../../../common/src/component/transform.h"
#include "../../../../utils/src/math.h"
#include "../../component/camera.h"
#include "../../renderer.h"
#include "../components/behaviour/titleCameraMove.h"
#include <iostream>

TitleCamera::TitleCamera(Scene* scene, Transform* parent)
    : GameObject(scene, parent, new TitleCameraMove(this))
{
    Vector3 viewPos = Vector3(10.0f, 40.0f, -40.0f);
    Matrix4 view    = Matrix4::CreateLookAt(viewPos, Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
    mTransform->SetWorldMatrix(view);
    Matrix4 projection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(40.0f), Renderer::GetWindowWidth(), Renderer::GetWindowHeight(), 0.1f, 150.0f);
    Camera* camera     = new Camera(this, projection);
    AddComponent(camera);
    camera->Use();
}