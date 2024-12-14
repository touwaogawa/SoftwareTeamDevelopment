#include "meshRenderer.h"
#include "../component.h"
#include "../gameObject.h"
#include "../mesh.h"
#include "../renderer.h"
#include "../scene.h"
#include "../shader.h"
#include "transform.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

MeshRenderer::MeshRenderer(GameObject* owner)
    : Component(owner)
{
    mOwner->GetScene()->GetRenderer()->AddMeshRenderer(this);
}
MeshRenderer::~MeshRenderer()
{
    mOwner->GetScene()->GetRenderer()->RemoveMeshRenderer(this);
}
void MeshRenderer::Draw(Shader* shader)
{
    shader->Use();
    GLint modelLoc = glGetUniformLocation(shader->GetProgram(), "model");

    Matrix4 model = mOwner->GetTransform()->GetWorldMatrix();
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.GetAsFloatPtr());

    mMesh->GetVAO()->Bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}