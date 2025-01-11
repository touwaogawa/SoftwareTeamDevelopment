#pragma once
#include "../../../../../common/src/component/behaviour.h"

class TitleCameraMove : public Behaviour {
public:
    explicit TitleCameraMove(GameObject* owner);
    ~TitleCameraMove() override = default;

    void Start() override;
    void Update() override;
    void LateUpdate() override;

private:
    float mAngle;
};