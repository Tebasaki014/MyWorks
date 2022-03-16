#include "SceneViewer.h"

Scene::Scene(CommonData* commonData, SceneViewer* viewer)
{
	this->commonData = commonData;
	this->wangine = commonData->wangine;
	this->input = wangine->input;
	this->camera = wangine->camera;
	this->viewer = viewer;
}

void Scene::ChangeScene(Scene* pNewScene)
{
	viewer->ChangeScene(pNewScene);
}

SceneViewer::SceneViewer()
{
	this->Initialize();	
}

SceneViewer::~SceneViewer()
{
	delete nowScene;
	delete commonData;
}

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

void DefaultScene::Start()
{
	//モデル設定
	player = new Player("Mummy");
	enemy = new Enemy("Mummy");
	ground = new Actor3D("ground");
	sky = new Actor3D("skydome");
	spr = new Actor2D(0, L"Resources/Reticle.png");

	//ライト初期化
	Light::GetInstance()->Initialize();
	Light::GetInstance()->SetDirection(Vector3::Nomalize(lightDir));

	//シェーダーコンパイル
	toon = new Shader(L"Resources/Shaders/OBJVS_toon.hlsl", L"Resources/Shaders/OBJPS_toon.hlsl");
	basic = new Shader(L"Resources/Shaders/OBJVS_basic.hlsl", L"Resources/Shaders/OBJPS_basic.hlsl");

	//地面設定
	ground->Scale = Vector3(10.0f, 10.0f, 10.0f);
	ground->position = Vector3(0.0f, -2.0f, 0.0f);

	//天球設定
	sky->Scale = Vector3(5.0f, 5.0f, 5.0f);
	sky->position = Vector3(0.0f, -80.0f, 0.0f);
	sky->RotationVector({ 0.25f, 0, 0 });

	//プレイヤー初期化
	player->SetCommon(commonData);
	player->Start();

	//敵初期化
	enemy->SetCommon(commonData);
	enemy->SetPlayer(player);
	enemy->position = { 0.0f, 0.0f,50.0f };
	enemy->Scale = { 1.5f, 1.5f, 1.5f };
	enemy->Start();

	//レティクル初期化
	spr->position = { 640, 280 };
	spr->Size = { 64, 64 };

	//ゲージ初期化
	Vector2 popo = { 100.0f, 100.0f };
	Vector2 pppo = { 1200.0f, 100.0f };
	gage = new CircleGage2D(popo, 128.0f);
	pgage = new CircleGage2D(pppo, 128.0f);
	XMFLOAT4 coll = { 0.3f, 1.0f, 0.3f, 1.0f };
	pgage->SetColor(coll);

	//カーソル非表示
	while (true)
	{
		int i = ShowCursor(0);
		if (i < 0) { break; }
	}
}

void DefaultScene::Update()
{
	sky->RotationVector({ lightRotAngle, 0, 0 });
	lightDir = Quaternion::RotationAround(lightDir, Vector3::Zero(), Vector3::WorldY(), lightRotAngle);
	Light::GetInstance()->SetDirection(Vector3::Nomalize(lightDir));

	//モデル更新
	ground->Update();
	sky->Update();
	player->Update();
	enemy->Update();
	spr->Update();

	wangine->GetWindowSize();

	//カーソル固定
	SetCursorPos(640, 280);

	//ゲージ更新
	float rate = (float)enemy->GetHP() / 50.0f;
	float prat = (float)player->GetHP() / 20.0f;
	gage->Update(rate);
	pgage->Update(prat);

	//if (input->IsKeyTouch(DIK_F)) {
	//	ppp->Live(player->position);
	//}

	//クリア
	if (enemy->isDead) {
		ChangeScene(new ClearScene(commonData, viewer));
	}
	//死亡
	else if (player->isDead) {
		ChangeScene(new OverScene(commonData, viewer));
	}
}

void DefaultScene::Draw()
{
	wangine->StartDraw3D();

	sky->Draw(*basic);
	ground->Draw(*toon);
	player->Draw(*toon);
	enemy->Draw(*toon);

	ParticleManager::GetInstance()->Draw(wangine->dx12->GetCommandList());

	wangine->EndDraw3D();

	wangine->StartDraw2D();
	spr->Draw(commonData->white);
	gage->Draw();
	pgage->Draw();
	wangine->EndDraw2D();
}

void DefaultScene::End()
{
	SDelete(enemy);
	SDelete(player);
	SDelete(spr);
	SDelete(ground);
	SDelete(sky);
	SDelete(ppp);
	SDelete(toon);
	SDelete(phong);
	SDelete(basic);
}

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

void ClearScene::Start()
{
	spr = new Actor2D(0, L"Resources/clear.png");
	spr->Size = { 1280.0f, 720.0f };
	spr->position = { 0.0f, 0.0f };
	spr->Update();
}

void ClearScene::Update()
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

void ClearScene::Draw()
{
	wangine->StartDraw2D();
	spr->Draw(commonData->white);
	wangine->EndDraw2D();
}

void ClearScene::End()
{
	SDelete(spr);
}

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