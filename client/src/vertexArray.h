#pragma once
#include <GL/glew.h>
class VertexArray {
public:
    enum class Layout {
        PosNorm,
        PosNormTex
    };

    VertexArray(const void* verts, unsigned int numVerts, Layout layout,
        const unsigned int* indices, unsigned int numIndices);
    ~VertexArray();

    void Bind();

    static GLuint GetVertexSize(VertexArray::Layout layout);

private:
    GLuint mVBO;
    GLuint mEBO;
    GLuint mVAO;
};