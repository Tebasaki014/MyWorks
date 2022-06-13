#include"TitleScene.h"
#include"DefaultScene.h"

void TitleScene::Start()
{
	spr = new Actor2D(0, L"Resources/title.png");
	spr->Size = { 1280.0f, 720.0f };
	spr->position = { 0.0f, 0.0f };
	spr->Update();
}

void TitleScene::Update()
{
	while (true)
	{
		int i = ShowCursor(1);
		if (i >= 0) { break; }
	}

	if (input->IsKeyDown(DIK_SPACE)) {
		ChangeScene(new DefaultScene(commonData, viewer));
	}
}

void TitleScene::Draw()
{
	wangine->StartDraw2D();
	spr->Draw(commonData->white);
	wangine->EndDraw2D();
}

void TitleScene::End()
{
	SDelete(spr);
}