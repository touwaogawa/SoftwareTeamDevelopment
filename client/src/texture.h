#pragma once
#include <string>

class Texture {
public:
    Texture();
    ~Texture() = default;
    bool Load(const std::string& fileName);
    void UnLoad();

    void SetActive(int index = 0);

    int GetWidth() const { return mWidth; }
    int GetHeight() const { return mHeight; }
    unsigned int GetTextureID() const { return mTextureID; }

    const std::string& GetFileName() const { return mFileName; }

private:
    std::string mFileName;
    unsigned int mTextureID;
    int mWidth;
    int mHeight;
};