#pragma once
#include "vertexArray.h"
#include <string>

class Mesh {
public:
    Mesh();
    ~Mesh();
    bool LoadObjFile(const std::string& fileName);
    void LoadTextureFile(const std::vector<std::string>& fileNames);
    void LoadTextureFile(const std::string& fileName);
    VertexArray* GetVertexArray() const { return mVertexArray; }
    class Texture* GetTexture(size_t index);

private:
    VertexArray* mVertexArray;
    std::vector<class Texture*> mTextures;
};