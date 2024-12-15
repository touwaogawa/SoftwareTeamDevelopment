#pragma once
#include "vertexArray.h"
#include <string>

class Mesh {
public:
    Mesh();
    ~Mesh();
    bool LoadObjFile(const std::string& fileName);
    VertexArray* GetVAO() const;
    unsigned int GetNumVerts() const { return mNumVerts; }

private:
    VertexArray* mVertexArray;
    unsigned int mNumVerts;
};