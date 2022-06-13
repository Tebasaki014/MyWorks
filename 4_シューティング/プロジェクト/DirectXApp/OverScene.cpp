#include"OverScene.h"
#include"TitleScene.h"

void OverScene::Start()
{
	spr = new Actor2D(0, L"Resources/over.png");
	spr->Size = { 1280.0f, 720.0f };
	spr->position = { 0.0f, 0.0f };
	spr->Update();
}

void OverScene::Update()
{
	while (true)
	{
		int i = ShowCursor(1);
		if (i >= 0) { break; }
	}


	if (input->IsKeyDown(DIK_SPACE)) {
		ChangeScene(new TitleScene(commonData, viewer));
	}
}

void OverScene::Draw()
{
	wangine->StartDraw2D();
	spr->Draw(commonData->white);
	wangine->EndDraw2D();
}

void OverScene::End()
{
	SDelete(spr);
}