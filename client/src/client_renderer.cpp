// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "client_renderer.h"
// #include "Texture.h"
// #include "Mesh.h"
#include <algorithm>
// #include "Shader.h"
// #include "VertexArray.h"
// #include "SpriteComponent.h"
// #include "MeshComponent.h"
#include <GL/glew.h>

Renderer::Renderer(Game* game)
	// :mGame(game)
	// ,mSpriteShader(nullptr)
	// ,mMeshShader(nullptr)
{
}

Renderer::~Renderer()
{
}

bool Renderer::Initialize()
{
	// SDL_DisplayMode displayMode;
	// SDL_GetCurrentDisplayMode(0, &displayMode); // 0番目のディスプレイ（通常はメインディスプレイ）の解像度を取得
	// int monitorWidth = displayMode.w;
	// int monitorHeight = displayMode.h;

	mScreenWidth = 500;
	mScreenHeight = 500;

	// // Set OpenGL attributes
	// // Use the core OpenGL profile
	// SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// // Specify version 3.3
	// SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	// SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// // Request a color buffer with 8-bits per RGBA channel
	// SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	// SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	// SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	// SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	// SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// // Enable double buffering
	// SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// // Force OpenGL to use hardware acceleration
	// SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 6)", 100, 100,
		static_cast<int>(mScreenWidth), static_cast<int>(mScreenHeight), 0);  // OpenGLフラグを削除
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	// SDLレンダラーを作成（OpenGLコンテキストは不要）
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);  // SDL_RENDERER_ACCELERATED はハードウェアアクセラレーションを使用
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

	// Create an OpenGL context
	// mContext = SDL_GL_CreateContext(mWindow);

	// Initialize GLEW
	// glewExperimental = GL_TRUE;
	// if (glewInit() != GLEW_OK)
	// {
	// 	SDL_Log("Failed to initialize GLEW.");
	// 	return false;
	// }

	// On some platforms, GLEW will emit a benign error code,
	// so clear it
	// glGetError();

	// // Make sure we can create/compile shaders
	// if (!LoadShaders())
	// {
	// 	SDL_Log("Failed to load shaders.");
	// 	return false;
	// }

	// // Create quad for drawing sprites
	// CreateSpriteVerts();

	return true;
}

void Renderer::Shutdown()
{
	// delete mSpriteVerts;
	// mSpriteShader->Unload();
	// delete mSpriteShader;
	// mMeshShader->Unload();
	// delete mMeshShader;
	// SDL_GL_DeleteContext(mContext);
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
}

// void Renderer::UnloadData()
// {
// 	// Destroy textures
// 	for (auto i : mTextures)
// 	{
// 		i.second->Unload();
// 		delete i.second;
// 	}
// 	mTextures.clear();

// 	// Destroy meshes
// 	for (auto i : mMeshes)
// 	{
// 		i.second->Unload();
// 		delete i.second;
// 	}
// 	mMeshes.clear();
// }

void Renderer::Draw()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderPresent(mRenderer);
}

// void Renderer::AddSprite(SpriteComponent* sprite)
// {
// 	// Find the insertion point in the sorted vector
// 	// (The first element with a higher draw order than me)
// 	int myDrawOrder = sprite->GetDrawOrder();
// 	auto iter = mSprites.begin();
// 	for (;
// 		iter != mSprites.end();
// 		++iter)
// 	{
// 		if (myDrawOrder < (*iter)->GetDrawOrder())
// 		{
// 			break;
// 		}
// 	}

// 	// Inserts element before position of iterator
// 	mSprites.insert(iter, sprite);
// }

// void Renderer::RemoveSprite(SpriteComponent* sprite)
// {
// 	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
// 	mSprites.erase(iter);
// }

// void Renderer::AddMeshComp(MeshComponent* mesh)
// {
// 	mMeshComps.emplace_back(mesh);
// }

// void Renderer::RemoveMeshComp(MeshComponent* mesh)
// {
// 	auto iter = std::find(mMeshComps.begin(), mMeshComps.end(), mesh);
// 	mMeshComps.erase(iter);
// }

// Texture* Renderer::GetTexture(const std::string& fileName)
// {
// 	Texture* tex = nullptr;
// 	auto iter = mTextures.find(fileName);
// 	if (iter != mTextures.end())
// 	{
// 		tex = iter->second;
// 	}
// 	else
// 	{
// 		tex = new Texture();
// 		if (tex->Load(fileName))
// 		{
// 			mTextures.emplace(fileName, tex);
// 		}
// 		else
// 		{
// 			delete tex;
// 			tex = nullptr;
// 		}
// 	}
// 	return tex;
// }

// Mesh* Renderer::GetMesh(const std::string & fileName)
// {
// 	Mesh* m = nullptr;
// 	auto iter = mMeshes.find(fileName);
// 	if (iter != mMeshes.end())
// 	{
// 		m = iter->second;
// 	}
// 	else
// 	{
// 		m = new Mesh();
// 		if (m->Load(fileName, this))
// 		{
// 			mMeshes.emplace(fileName, m);
// 		}
// 		else
// 		{
// 			delete m;
// 			m = nullptr;
// 		}
// 	}
// 	return m;
// }

// bool Renderer::LoadShaders()
// {
// 	// Create sprite shader
// 	mSpriteShader = new Shader();
// 	if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
// 	{
// 		return false;
// 	}

// 	mSpriteShader->SetActive();
// 	// Set the view-projection matrix
// 	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);
// 	mSpriteShader->SetMatrixUniform("uViewProj", viewProj);

// 	// Create basic mesh shader
// 	mMeshShader = new Shader();
// 	if (!mMeshShader->Load("Shaders/Phong.vert", "Shaders/Phong.frag"))
// 	{
// 		return false;
// 	}

// 	mMeshShader->SetActive();
// 	// Set the view-projection matrix
// 	mView = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
// 	mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f),
// 		mScreenWidth, mScreenHeight, 25.0f, 10000.0f);
// 	mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);
// 	return true;
// }

// void Renderer::CreateSpriteVerts()
// {
// 	float vertices[] = {
// 		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // top left
// 		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // top right
// 		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // bottom right
// 		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // bottom left
// 	};

// 	unsigned int indices[] = {
// 		0, 1, 2,
// 		2, 3, 0
// 	};

// 	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
// }

// void Renderer::SetLightUniforms(Shader* shader)
// {
// 	// Camera position is from inverted view
// 	Matrix4 invView = mView;
// 	invView.Invert();
// 	shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
// 	// Ambient light
// 	shader->SetVectorUniform("uAmbientLight", mAmbientLight);
// 	// Directional light
// 	shader->SetVectorUniform("uDirLight.mDirection",
// 		mDirLight.mDirection);
// 	shader->SetVectorUniform("uDirLight.mDiffuseColor",
// 		mDirLight.mDiffuseColor);
// 	shader->SetVectorUniform("uDirLight.mSpecColor",
// 		mDirLight.mSpecColor);
// }

void Renderer::CalculateMax16x9Size(){
	float aspectRatio = 16.0f / 9.0f;

    // 画面幅に合わせた高さを計算
    int heightForWidth = static_cast<int>(mScreenWidth / aspectRatio);

    if (heightForWidth <= mScreenHeight) {
        // 画面幅を基準にサイズを設定
        mGameScreenWidth = mScreenWidth;
        mGameScreenHeight = heightForWidth;
    } else {
        // 画面高さを基準にサイズを設定
        mGameScreenHeight = mScreenHeight;
        mGameScreenWidth = static_cast<int>(mScreenHeight * aspectRatio);
    }
}