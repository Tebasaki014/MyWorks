#include "SceneViewer.h"
#include"TitleScene.h"

void SceneViewer::ChangeScene(Scene* pNewScene)
{
	nowScene->End();
	SDelete(nowScene);
	nowScene = pNewScene;
	nowScene->Start();
}

void SceneViewer::Initialize()
{
	//召喚魔法
	commonData = new CommonData();
	commonData->wangine->Initialize();

	nowScene = new TitleScene(commonData, this);
	nowScene->Start();
}

void SceneViewer::End()
{
	SDelete(nowScene);
	commonData->wangine->End();
	SDelete(commonData->wangine);
	SDelete(commonData);
}

void SceneViewer::Update()
{
	if (commonData->wangine->input->IsKeyDown(DIK_ESCAPE)) {
		ChangeScene(new TitleScene(commonData, this));
	}
	nowScene->Update();
}

bool SceneViewer::Draw()
{
	//毎フレーム処理
	if (!commonData->wangine->ScreenClear(commonData->clearColor)) { return false; }
	nowScene->Draw();
	//描画処理ここまで
	commonData->wangine->ScreenFlip();

	return true;
}