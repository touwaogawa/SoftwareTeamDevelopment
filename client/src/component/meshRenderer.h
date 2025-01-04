#pragma once
#include "../../../common/src/component.h"
#include "../../../utils/src/math.h"
#include <string>

class MeshRenderer : public Component {
public:
    explicit MeshRenderer(class GameObject* owner);
    MeshRenderer(class GameObject* owner, const std::string& fileName);
    ~MeshRenderer() override;
    void SetMesh(class Mesh* mesh);
    void Load(const std::string& fileName);
    void Draw(class Shader* shader);
    Matrix4 mOffset;

private:
    class Mesh* mMesh;
    class Renderer* mRenderer;
};