#define STB_IMAGE_IMPLEMENTATION
#include "texture.h"
#include <GL/glew.h>
#include <iostream>
#include <stb/stb_image.h>

Texture::Texture()
    : mTextureID(0)
    , mWidth(0)
    , mHeight(0)
{
}

bool Texture::Load(const std::string& fileName)
{
    int nrChannels;
    mFileName = fileName;
    // stb_imageで画像を読み込む（ピクセルデータを取得）
    const char* f       = fileName.c_str();
    unsigned char* data = stbi_load(f, &mWidth, &mHeight, &nrChannels, 0);

    if (data) {
        // OpenGLのテクスチャオブジェクトを生成
        glGenTextures(1, &mTextureID);

        // テクスチャをバインド
        glBindTexture(GL_TEXTURE_2D, mTextureID);

        // テクスチャの設定
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     // 横方向のラッピング
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     // 縦方向のラッピング
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // テクスチャが小さくなったときのフィルタリング
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // テクスチャが大きくなったときのフィルタリング

        // 画像のピクセルデータをOpenGLにアップロード
        if (nrChannels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        } else if (nrChannels == 4) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        } else {
            std::cout << "Unsupported image format!" << std::endl;
        }

        // ミップマップの生成
        glGenerateMipmap(GL_TEXTURE_2D);

        // メモリを解放
        stbi_image_free(data);

    } else {
        std::cout << "Failed to load texture! : " << fileName << std::endl;
        return false;
    }
    return true;
}

void Texture::CreateTextureFromAtlas(const unsigned char* atlasData, int atlasWidth, int atlasHeight)
{
    mTextureID;
    glGenTextures(1, &mTextureID);
    glBindTexture(GL_TEXTURE_2D, mTextureID);

    // OpenGL のテクスチャパラメータを設定
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // アトラスをテクスチャとしてアップロード
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, atlasWidth, atlasHeight, 0, GL_RED, GL_UNSIGNED_BYTE, atlasData);
}

void Texture::UnLoad()
{
    glDeleteTextures(1, &mTextureID);
}

void Texture::SetActive(int index)
{
    glActiveTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, mTextureID);
}
