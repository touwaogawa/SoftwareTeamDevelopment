#pragma once

#include "../../../common/src/component.h"
#include <string>

class MeshRenderer : public Component {
public:
    explicit MeshRenderer(class GameObject* owner);
    ~MeshRenderer() override;
    void SetMesh(class Mesh* mesh);
    void Load(const std::string& fileName);
    void Draw(class Shader* shader);

private:
    class Mesh* mMesh;
    class Renderer* mRenderer;
};