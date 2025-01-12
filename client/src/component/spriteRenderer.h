#pragma once

#include "../../../common/src/component.h"
#include "../../../utils/src/math.h"
#include <string>

class GameObject;
class Texture;
class Shader;
class SpriteRenderer : public Component {
public:
    SpriteRenderer(GameObject* owner, int order = 0);
    ~SpriteRenderer() override;

    virtual void Draw(Shader* shader);
    void SetTexture(Texture* texture);

    int GetDrawOrder() const { return mDrawOrder; }
    int GetTexHeight() const { return mTexHeight; }
    int GetTexWidth() const { return mTexWidth; }

    void SetVisible(bool visible) { mVisible = visible; }
    bool GetVisible() const { return mVisible; }

    void SetUseCustomColor(bool useCustomColor) { mUseCustomColor = useCustomColor; }
    bool GetUseCustomColor() const { return mUseCustomColor; }

    void SetCustomColor(Vector3 customColor) { mCustomColor = customColor; }
    Vector3 GetCustomColor() const { return mCustomColor; }

    void SetFrameSize(Vector2 frameSize) { mFrameSize = frameSize; }
    void SetFrameIndex(Vector2 frameIndex) { mFrameIndex = frameIndex; }
    const Vector2& GetFrameSize() const { return mFrameSize; }
    const Vector2& GetFrameIndex() const { return mFrameIndex; }

private:
    void Enable() override;
    void Disable() override;

    Texture* mTexture;
    int mTexWidth;
    int mTexHeight;
    Vector2 mFrameSize;
    Vector2 mFrameIndex;
    int mDrawOrder;
    bool mVisible;
    bool mUseCustomColor;
    Vector3 mCustomColor;
};
