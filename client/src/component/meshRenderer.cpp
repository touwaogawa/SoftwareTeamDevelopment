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

MeshRenderer::MeshRenderer(GameObject* owner, const std::string& objFileName, const std::string& textureFileName, bool isEffect)
    : Component(owner)
    , mTextureIndex(0)
    , mIsEffect(isEffect)
{
    mMesh = Renderer::GetMesh(objFileName);
    mMesh->SetTexture(Renderer::GetTexture(textureFileName));
    if (mIsEffect) {
        Renderer::AddEffectRenderer(this);
    } else {
        Renderer::AddMeshRenderer(this);
    }
}
MeshRenderer::~MeshRenderer()
{
    if (mIsEffect) {
        Renderer::RemoveEffectRenderer(this);
    } else {
        Renderer::RemoveMeshRenderer(this);
    }
}

void MeshRenderer::Draw(Shader* shader)
{

    Matrix4 model = mOwner->GetTransform()->GetWorldMatrix() * mOffset;
    shader->SetMatrixUniform("model", model);

    Texture* t = mMesh->GetTexture(mTextureIndex);
    if (t) {
        t->SetActive();
    }

    VertexArray* va = mMesh->GetVertexArray();
    va->Bind();

    glDrawArrays(GL_TRIANGLES, 0, va->GetNumVerts());

    glBindVertexArray(0);
}

void MeshRenderer::Enable()
{
    if (mIsEffect) {
        Renderer::AddEffectRenderer(this);
    } else {
        Renderer::AddMeshRenderer(this);
    }
}
void MeshRenderer::Disable()
{
    if (mIsEffect) {
        Renderer::RemoveEffectRenderer(this);
    } else {
        Renderer::RemoveMeshRenderer(this);
    }
}