#include "vertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray(const void* verts, unsigned int numVerts, Layout layout)
    : mNumVerts(numVerts)
{
    // Create vertex array
    glGenVertexArrays(1, &mVAO);
    glBindVertexArray(mVAO);

    // Create vertex buffer
    glGenBuffers(1, &mVBO);
    glBindBuffer(GL_ARRAY_BUFFER, mVBO);
    glBufferData(GL_ARRAY_BUFFER, numVerts * sizeof(Vertex), verts, GL_STATIC_DRAW);

    // Specify the vertex attributes
    if (layout == Layout::PosNorm) {

        // Position is 3 floats
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0);
        // Normal is 3 floats
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6,
            reinterpret_cast<void*>(sizeof(float) * 3));
    } else if (layout == Layout::PosNormTex) {
        // Position is 3 floats
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
        // Normal is 3 floats
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
            reinterpret_cast<void*>(sizeof(float) * 3));
        // Texture coordinates is 2 floats
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8,
            reinterpret_cast<void*>(sizeof(float) * 6));
    }
    glBindVertexArray(0);
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