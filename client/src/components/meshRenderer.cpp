#include "meshRenderer.h"
#include "../../../common/src/component.h"
#include "../../../common/src/components/transform.h"
#include "../../../common/src/gameObject.h"
#include "../mesh.h"
#include "../renderer.h"
#include "../scene.h"
#include "../shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

MeshRenderer::MeshRenderer(GameObject* owner)
    : Component(owner)
{
    mOwner->GetScene()->GetRenderer()->AddMeshRenderer(this);
}
MeshRenderer::~MeshRenderer()
{
    mOwner->GetScene()->GetRenderer()->RemoveMeshRenderer(this);
}

void MeshRenderer::SetMesh(Mesh* mesh)
{
    mMesh = mesh;
}

void MeshRenderer::Load(const std::string& fileName)
{
    Mesh* mesh = mOwner->GetScene()->GetRenderer()->GetMesh(fileName);
    SetMesh(mesh);
}
void MeshRenderer::Draw(Shader* shader)
{
    shader->Use();
    GLint modelLoc = glGetUniformLocation(shader->GetProgram(), "model");

    Matrix4 model = mOwner->GetTransform()->GetWorldMatrix();
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.GetAsFloatPtr());

    mMesh->GetVAO()->Bind();
    // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, mMesh->GetNumVerts());

    glBindVertexArray(0);
}