#pragma once
#include "vertexArray.h"
#include <string>
class Mesh {
public:
    Mesh();
    ~Mesh();
    bool LoadObjFile(const std::string& fileName);
    VertexArray* GetVAO() const;

private:
    VertexArray* mVertexArray;
};