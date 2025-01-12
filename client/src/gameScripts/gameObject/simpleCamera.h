#pragma once
#include "../../../../common/src/gameObject.h"
#include "../../../../utils/src/math.h"
#include "../../renderer.h"

class SimpleCamera : public GameObject {
public:
    SimpleCamera(Matrix4 projection
        = Matrix4::CreatePerspectiveFOV(Math::ToRadians(40.0f),
            Renderer::GetWindowWidth(),
            Renderer::GetWindowHeight(),
            0.1f,
            150.0f),
        bool initialUse = false);
    ~SimpleCamera() override = default;
};