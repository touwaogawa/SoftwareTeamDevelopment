#include "spriteRenderer.h"
#include "../../../common/src/component/transform.h"
#include "../../../common/src/gameObject.h"
#include "../renderer.h"
#include "../shader.h"
#include "../texture.h"
#include <iostream>

SpriteRenderer::SpriteRenderer(GameObject* owner, int order)
    : Component(owner)
    , mTexWidth(0)
    , mTexHeight(0)
    , mFrameSize(Vector2(1.0f, 1.0f))
    , mFrameIndex(Vector2())
    , mDrawOrder(order)
    , mVisible(true)
    , mUseCustomColor(false)
    , mCustomColor(Vector3(1.0f, 0.0f, 1.0f))
{
    Renderer::AddSpriteRenderer(this);
}

SpriteRenderer::~SpriteRenderer()
{
    // std::cout << "~Sprite" << std::endl;
    Renderer::RemoveSpriteRenderer(this);
}

void SpriteRenderer::Draw(Shader* shader)
{
    if (mTexture) {
        // Scale the quad by the width/height of texture
        Matrix4 scaleMat = Matrix4::CreateScale(
            mTexWidth * mFrameSize.x,
            mTexHeight * mFrameSize.y,
            1.0f);

        Matrix4 model = scaleMat * mOwner->GetTransform()->GetWorldMatrix();

        // Since all sprites use the same shader/vertices,
        // the game first sets them active before any sprite draws

        // Set world transform
        shader->SetMatrixUniform("model", model);
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
void SpriteRenderer::SetTexture(Texture* texture)
{
    mTexture = texture;
    // Set width/height
    mTexWidth  = texture->GetWidth();
    mTexHeight = texture->GetHeight();
}

void SpriteRenderer::Enable()
{
    Renderer::AddSpriteRenderer(this);
}
void SpriteRenderer::Disable()
{
    Renderer::RemoveSpriteRenderer(this);
}