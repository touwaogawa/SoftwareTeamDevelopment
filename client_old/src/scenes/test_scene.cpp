#include "test_scene.h"

TestScene::TestScene()
    : mFrameCount(0)
{
}

// オブジェクトのロード
void TestScene::Load()
{
}
// 最初のフレームだけ実行される値
void TestScene::Start()
{
}
// 動的物理演算前に毎フレーム実行される
void TestScene::Update()
{
}
// 動的物理演算後に毎フレーム実行される
void TestScene::LateUpdate()
{
}