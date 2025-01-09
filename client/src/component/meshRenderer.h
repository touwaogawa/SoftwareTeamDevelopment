#pragma once
#include "../../../common/src/component.h"
#include "../../../utils/src/math.h"
#include <string>
#include <vector>
class MeshRenderer : public Component {
public:
    MeshRenderer(class GameObject* owner, const std::string& objFileName, const std::vector<std::string>& textureFileNames);
    MeshRenderer(class GameObject* owner, const std::string& objFileName, const std::string& textureFileName);
    ~MeshRenderer() = default;
    void SetMesh(class Mesh* mesh) { mMesh = mesh; }
    void LoadObj(const std::string& fileName);
    void LoadTextures(const std::string& fileName);
    void Draw(class Shader* shader);
    Matrix4 mOffset;

private:
    class Mesh* mMesh;
    size_t mTextureIndex;
};