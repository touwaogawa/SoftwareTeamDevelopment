#include "vertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray(const void* verts, unsigned int numVerts, Layout layout,
    const unsigned int* indices, unsigned int numIndices)
{
    // Create vertex array
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    unsigned vertexSize = GetVertexSize(layout);

    // Create vertex buffer
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, numVerts * vertexSize, verts, GL_STATIC_DRAW);

    // Create index buffer
    glGenBuffers(1, &mEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    // Specify the vertex attributes
    if (layout == Layout::PosNorm) {

        // Position is 3 floats
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
        // Normal is 3 floats
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize,
            reinterpret_cast<void*>(sizeof(float) * 3));
    } else if (layout == Layout::PosNormTex) {
        // Position is 3 floats
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
        // Normal is 3 floats
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize,
            reinterpret_cast<void*>(sizeof(float) * 3));
        // Texture coordinates is 2 floats
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexSize,
            reinterpret_cast<void*>(sizeof(float) * 6));
    }
}

VertexArray::~VertexArray()
{
    glDeleteBuffers(1, &mVBO);
    glDeleteBuffers(1, &mEBO);
    glDeleteVertexArrays(1, &mVAO);
}

void VertexArray::Bind()
{
    glBindVertexArray(mVAO);
}

GLuint VertexArray::GetVertexSize(VertexArray::Layout layout)
{
    GLuint vertexSize = 8 * sizeof(float);
    if (layout == Layout::PosNorm) {
        vertexSize = 6 * sizeof(float);
    } else if (layout == Layout::PosNormTex) {
        vertexSize = 8 * sizeof(float);
    }
    return vertexSize;
}
