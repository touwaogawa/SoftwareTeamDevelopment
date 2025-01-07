#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

class VertexArray {
public:
    enum class Layout {
        PosNorm,
        PosNormTex
    };

    VertexArray(const void* verts, unsigned int numVerts, Layout layout);
    ~VertexArray();
    unsigned int GetNumVerts() const { return mNumVerts; }

    void Bind();

private:
    GLuint mVBO;
    GLuint mEBO;
    GLuint mVAO;
    unsigned int mNumVerts;
};