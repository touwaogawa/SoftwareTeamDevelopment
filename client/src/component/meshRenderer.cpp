#include "meshRenderer.h"
#include "../../../common/src/component.h"
#include "../../../common/src/component/transform.h"
#include "../../../common/src/gameObject.h"
#include "../../../common/src/scene.h"
#include "../../../utils/src/math.h"
#include "../mesh.h"
#include "../renderer.h"
#include "../shader.h"
#include "../texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

MeshRenderer::MeshRenderer(GameObject* owner, const std::string& objFileName, const std::vector<std::string>& textureFileNames)
    : Component(owner)
    , mTextureIndex(0)
{
    Renderer::AddMeshRenderer(this);
    LoadObj(objFileName);
    mMesh->LoadTextureFile(textureFileNames);
}
MeshRenderer::MeshRenderer(GameObject* owner, const std::string& objFileName, const std::string& textureFileName)
    : Component(owner)
    , mTextureIndex(0)
{
    Renderer::AddMeshRenderer(this);
    LoadObj(objFileName);
    mMesh->LoadTextureFile(textureFileName);
}

void MeshRenderer::LoadObj(const std::string& fileName)
{
    mMesh = Renderer::GetMesh(fileName);
}
void MeshRenderer::LoadTextures(const std::string& fileName)
{
    mMesh->LoadTextureFile(fileName);
}

void MeshRenderer::Draw(Shader* shader)
{

    Matrix4 model = mOffset * mOwner->GetTransform()->GetWorldMatrix();
    shader->SetMatrixUniform("model", model);

    Texture* t = mMesh->GetTexture(mTextureIndex);
    if (t) {
        t->SetActive();
    }

    VertexArray* va = mMesh->GetVertexArray();
    va->Bind();

    // glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, va->GetNumVerts());

    glBindVertexArray(0);
}