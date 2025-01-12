#pragma once
#include "../../../common/src/component.h"
#include "../../../utils/src/math.h"
#include <string>
#include <vector>
class MeshRenderer : public Component {
public:
    MeshRenderer(class GameObject* owner, const std::string& objFileName, const std::string& textureFileName, bool isEffect = false);
    ~MeshRenderer() override;
    void SetMesh(class Mesh* mesh) { mMesh = mesh; }
    void Draw(class Shader* shader);

    Matrix4 mOffset;

private:
    void Enable() override;
    void Disable() override;

    class Mesh* mMesh;
    size_t mTextureIndex;

    const bool mIsEffect;
};