// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
//
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "BallActor.h"
#include "BallMove.h"
#include "Game.h"
#include "LevelLoader.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Renderer.h"

BallActor::BallActor(Game* game)
    : Actor(game)
    , mLifeSpan(2.0f)
{
    // SetScale(10.0f);
    MeshComponent* mc = new MeshComponent(this);
    Mesh* mesh        = GetGame()->GetRenderer()->GetMesh("Assets/Sphere.gpmesh");
    mc->SetMesh(mesh);
    BallMove* move = new BallMove(this);
    move->SetForwardSpeed(1500.0f);
}

void BallActor::UpdateActor(float deltaTime)
{
    Actor::UpdateActor(deltaTime);

    mLifeSpan -= deltaTime;
    if (mLifeSpan < 0.0f) {
        SetState(EDead);
    }
}

void BallActor::HitTarget()
{
}

void BallActor::LoadProperties(const rapidjson::Value& inObj)
{
    Actor::LoadProperties(inObj);
    JsonHelper::GetFloat(inObj, "lifespan", mLifeSpan);
}

void BallActor::SaveProperties(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObj) const
{
    Actor::SaveProperties(alloc, inObj);
    JsonHelper::AddFloat(alloc, inObj, "lifespan", mLifeSpan);
}
