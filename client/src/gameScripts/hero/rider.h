#pragma once
#include "../../gameObject.h"
class Rider : public GameObject {
public:
    Rider(Scene* scene, Transform* parent);
    ~Rider() override;

private:
    class MeshRenderer* mMeshRenderer;
};