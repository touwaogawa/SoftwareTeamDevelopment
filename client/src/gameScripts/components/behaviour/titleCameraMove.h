#pragma once
#include "../../../../../common/src/component/behaviour.h"

class CameraComponent;
class TitleCameraMove : public Behaviour {
public:
    explicit TitleCameraMove(GameObject* owner, CameraComponent* camera);
    ~TitleCameraMove() override = default;

    void Start() override;
    void Update() override;
    void LateUpdate() override;

    // void Awake() override;
    // void OnEnable() override;

private:
    float mAngle;
    const int& mCurrentframe;
    CameraComponent* const mCamera;
};