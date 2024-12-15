#pragma once
#include "../../gameObject.h"

class Bey : public GameObject {
public:
    Bey(class Scene* scene, class Transform* parent);
    ~Bey() override;

private:
    class MeshRenderer* mMeshRenderer;
};