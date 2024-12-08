#pragma once

#include "component.h"

class Behaviour : public Component {
public:
    // void Awake();
    void Start();
    void Update();
    void LateUpdate();
    void OnEnable();
    void OnDisable();
    void OnDestory();

    bool Getenable() const;
    void SetEnable();

private:
    bool mEnable;
};