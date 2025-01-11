#pragma once
#include "vertexArray.h"
#include <string>

class Texture;
class Mesh {
public:
    Mesh();
    ~Mesh();
    bool LoadObjFile(const std::string& fileName);
    void SetTexture(Texture* texture) { mTextures.emplace_back(texture); }
    VertexArray* GetVertexArray() const { return mVertexArray; }
    Texture* GetTexture(size_t index);

private:
    VertexArray* mVertexArray;
    std::vector<Texture*> mTextures;
};