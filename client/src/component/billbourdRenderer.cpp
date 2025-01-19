#include "billbourdRenderer.h"
#include "../../../common/src/component/transform.h"
#include "../../../common/src/gameObject.h"
#include "../renderer.h"
#include "../shader.h"
#include "../texture.h"
#include <iostream>

BillbourdRenderer::BillbourdRenderer(GameObject* owner, const std::string& imageFileName, bool isSpherical, bool isAdd)
    : Component(owner)
    , mTexWidth(0)
    , mTexHeight(0)
    , mFrameSize(Vector2(1.0f, 1.0f))
    , mFrameIndex(Vector2())
    , mVisible(true)
    , mUseCustomColor(false)
    , mCustomColor(Vector3(1.0f, 0.0f, 1.0f))
    , mIsSpherical(isSpherical)
    , mIsAdd(isAdd)
{
    if (mIsAdd) {
        Renderer::AddBillbourdRenderer_add(this);
    } else {
        Renderer::AddBillbourdRenderer(this);
    }

    SetTexture(Renderer::GetTexture(imageFileName));
}

BillbourdRenderer::~BillbourdRenderer()
{
    // std::cout << "~Billbourd" << std::endl;
    if (mIsAdd) {
        Renderer::RemoveBillbourdRenderer_add(this);
    } else {
        Renderer::RemoveBillbourdRenderer(this);
    }
}

void BillbourdRenderer::Draw(Shader* shader)
{
    if (mTexture) {
        // Scale the quad by the width/height of texture
        Matrix4 scaleMat = Matrix4::CreateScale(
            mTexWidth * mFrameSize.x,
            mTexHeight * mFrameSize.y,
            1.0f);

        Matrix4 model = scaleMat * mOwner->GetTransform()->GetWorldMatrix();

        // Since all Billbourds use the same shader/vertices,
        // the game first sets them active before any Billbourd draws

        // Set world transform
        shader->SetMatrixUniform("model", model);

        if (mIsSpherical) {
            shader->SetIntUniform("isSpherical", 1);
        } else {
            shader->SetIntUniform("isSpherical", 0);
        }

        shader->SetVector2Uniform("frameSize", mFrameSize);
        shader->SetVector2Uniform("frameIndex", mFrameIndex);
        if (mUseCustomColor) {
            shader->SetIntUniform("useCustomColor", 1);
            shader->SetVector3Uniform("customColor", mCustomColor);
        } else {
            shader->SetIntUniform("useCustomColor", 0);
        }
        // Set current texture
        mTexture->SetActive();
        // Draw quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
}
void BillbourdRenderer::SetTexture(Texture* texture)
{
    mTexture = texture;
    // Set width/height
    mTexWidth  = texture->GetWidth();
    mTexHeight = texture->GetHeight();
}

void BillbourdRenderer::Enable()
{
    if (mIsAdd) {
        Renderer::AddBillbourdRenderer_add(this);
    } else {
        Renderer::AddBillbourdRenderer(this);
    }
}
void BillbourdRenderer::Disable()
{
    if (mIsAdd) {
        Renderer::RemoveBillbourdRenderer_add(this);
    } else {
        Renderer::RemoveBillbourdRenderer(this);
    }
}