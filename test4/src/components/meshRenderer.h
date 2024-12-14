#pragma once

#include "../component.h"
#include <string>

class MeshRenderer : public Component {
public:
    explicit MeshRenderer(class GameObject* owner);
    ~MeshRenderer() override;
    void SetMesh(const std::string& fileName);
    void Draw(class Shader* shader);

private:
    class Mesh* mMesh;
};