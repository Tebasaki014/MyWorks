#include "GameScene.h"
#include "Model.h"
#include "Collision.h"

#include <cassert>
#include <sstream>
#include <iomanip>

using namespace std;



using namespace DirectX;

struct BogusBoxCollision
{
	XMFLOAT3 posision;
	float radiusX,
		radiusZ,
		edgeXA,
		edgeXB,
		edgeZA,
		edgeZB;

	void Set(XMFLOAT3 pos, float radX, float radZ) {
		posision = pos;
		radiusX = radX;
		radiusZ = radZ;

		edgeXA = posision.x - radiusX;
		edgeXB = posision.x + radiusX;
		edgeZA = posision.z - radiusZ;
		edgeZB = posision.z + radiusZ;
	}

	static bool IsHitAtoB(BogusBoxCollision player, BogusBoxCollision wall) {

		if (((player.edgeXA > wall.edgeXA && player.edgeXA < wall.edgeXB) ||
			(wall.edgeXA > player.edgeXA && wall.edgeXA < player.edgeXB)) &&
			((player.edgeZA > wall.edgeZA && player.edgeZA < wall.edgeZB) ||
			(wall.edgeZA > player.edgeZA && wall.edgeZA < player.edgeZB))) {
			return true;
		}
		else {
			return false;
		}
	}
};
GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	
}
//グローバル
const float cameraDistance = 10.0f;
float angleXZ = 0.0f, angleYZ = 0.0f;
Vector2 mouPo(0.0f, 0.0f);
Vector2 mouMo(0.0f, 0.0f);
Vector2 center(1535 / 2, 840 / 2);
//Vector2 center(1920 / 2, 1080 / 2);
Vector3 playerVel(0.0f, 0.0f, 0.0f);
Vector3 playerDirec(0.0f, 0.0f, 0.0f);

const float pi = 3.141592653f;
const float dZone = 128;
BogusBoxCollision playerCol, wallCol,itemCol,floorCol,goalCol;
void PlayerUpdate(Object3d* objFighter, Input* input);
XMFLOAT3 playerPos;
XMFLOAT3 cameraPos;
XMFLOAT3 cameraTergetPos;
int start;
vector<int>x;
vector<int>z;
void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio * audio)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	if (!Sprite::LoadTexture(1, L"Resources/background.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(10, L"Resources/startBG.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(11, L"Resources/title1.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(12, L"Resources/Bottom.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(13, L"Resources/miniMap.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(14, L"Resources/gamescreen.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(15, L"Resources/miniMapPlayer.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(16, L"Resources/Item.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(17, L"Resources/GameOver.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(18, L"Resources/GameClear.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(19, L"Resources/miniMapGoal.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(20, L"Resources/gage1.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(21, L"Resources/gage2.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(22, L"Resources/gage3.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(23, L"Resources/gage4.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(24, L"Resources/gage5.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(25, L"Resources/gage6.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(26, L"Resources/gage7.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(27, L"Resources/gage8.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(28, L"Resources/gage9.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(29, L"Resources/gage10.png")) {
		assert(0);
		return;
	}
	if (!Sprite::LoadTexture(30, L"Resources/gageBlank.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(31, L"Resources/clear1.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(32, L"Resources/clear2.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(33, L"Resources/clear3.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(34, L"Resources/clear4.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(35, L"Resources/clear5.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(36, L"Resources/clear6.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(37, L"Resources/clear7.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(38, L"Resources/clear8.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(39, L"Resources/clear9.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(40, L"Resources/Score2.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(41, L"Resources/Energy2.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(50, L"Resources/0.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(51, L"Resources/1.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(52, L"Resources/2.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(53, L"Resources/3.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(54, L"Resources/4.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(55, L"Resources/5.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(56, L"Resources/6.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(57, L"Resources/7.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(58, L"Resources/8.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(59, L"Resources/9.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(60, L"Resources/X.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(61, L"Resources/Item2.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(62, L"Resources/HighScore.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(62, L"Resources/HighScore.png")) {
		assert(0);
		return;

	}if (!Sprite::LoadTexture(63, L"Resources/Heal.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(64, L"Resources/left.png")) {
		assert(0);
		return;

	}
	if (!Sprite::LoadTexture(65, L"Resources/right.png")) {
		assert(0);
		return;

	}
	modelFloor = Model::CreateFromOBJ("floor2");
	modelWall = Model::CreateFromOBJ("wall");
	modelPlayer = Model::CreateFromOBJ("gurumet");
	modelItem = Model::CreateFromOBJ("item");
	modelGoal = Model::CreateFromOBJ("goal");
	//スタートシーン用	

	startScreen = Sprite::Create(10, { 0,0 });
	Bottom = Sprite::Create(12, { 1920 / 2-40,1080 / 2 });
	title = Sprite::Create(11, { 0,0 });
	//ゲームシーン
	playerObj = Object3d::Create();
	playerObj->SetModel(modelPlayer);
	miniMapPlayer = Sprite::Create(15, { 0,0 });
	BG = Sprite::Create(10, XMFLOAT2{ 0,0 });
	objGoal = Object3d::Create();
	itemRot = {90,0,0};
	//マップ
	miniMap=Sprite::Create(13, miniMapPos);
	miniMap->SetSize(miniMapSize);
	miniMapChipX = miniMapSize.x / mapXcount;
	miniMapChipZ = miniMapSize.y / mapZcount;
	miniMapChipXsize = miniMapChipX * 1.5f;
	miniMapChipZsize = miniMapChipZ * 1.5f;
	miniMapGoal = Sprite::Create(19, { 0,0 });

	for (int zi = 0; zi < mapZcount; zi++)
	{
		for (int xi = 0; xi < mapXcount; xi++)
		{
			if (floor[zi][xi] == 0)
			{
				objFloor.push_back(Object3d::Create());
				floorPos.push_back(XMFLOAT3(xi*floorSize*scale, -floorSize*scaleY, zi*floorSize*scale));
				x.push_back(xi);
				z.push_back(zi);
				
			}
			if (floor[zi][xi] == 1)
			{
				
				objWall.push_back(Object3d::Create());
				wallPos.push_back(XMFLOAT3(xi*floorSize*scale, 0, zi*floorSize*scale));
				

			}
			if (floor[zi][xi] == 2)
			{
				objFloor.push_back(Object3d::Create());
				floorPos.push_back(XMFLOAT3(xi*floorSize*scale, -floorSize * scaleY, zi*floorSize*scale));
				objItem.push_back(Object3d::Create());
				itemPos.push_back({ xi*floorSize*scale, 0, zi*floorSize*scale });
				x.push_back(xi);
				z.push_back(zi);
				miniMapItem.push_back(Sprite::Create(16, {0,0}));
				miniMapItemPos.push_back(XMFLOAT2{miniMapPos.x+miniMapChipX*-xi+miniMapSize.x,miniMapPos.y+miniMapChipZ*zi});
				getItemNum.push_back(false);
			}
			if (zi == 25 && xi ==12)
			{
				playerObj->SetPosition({ xi*floorSize*scale,0,zi*floorSize*scale });
				miniMapPlayerPos = XMFLOAT2{ miniMapPos.x + miniMapChipX * -xi+miniMapSize.x,miniMapPos.y + miniMapChipZ * zi };
			}
			if (floor[zi][xi] == 3)
			{
				
		        goalPos = XMFLOAT3(xi*floorSize*scale, 0, zi*floorSize*scale);
				miniMapGoalPos = XMFLOAT2{ miniMapPos.x + miniMapChipX * -xi + miniMapSize.x,miniMapPos.y + miniMapChipZ * zi };
				
			}
		}
	}

	miniMapGoal->SetPosition(miniMapGoalPos);
	miniMapGoal->SetSize(XMFLOAT2{ miniMapChipXsize,miniMapChipZsize });
	objGoal->SetModel(modelGoal);
	objGoal->SetPosition(goalPos);
	for (int i = 0; i < objFloor.size(); i++)
	{
		objFloor[i]->SetModel(modelFloor);
	}
	for (int i = 0; i < objWall.size(); i++)
	{
		objWall[i]->SetModel(modelWall);
	}
	for (int i = 0; i < objItem.size(); i++)
	{
		objItem[i]->SetModel(modelItem);
	}
	for (int i = 0; i < objFloor.size(); i++)
	{
	
		objFloor[i]->SetPosition(floorPos[i]);
	}
	for (int i = 0; i < objWall.size(); i++)
	{
		objWall[i]->SetPosition(wallPos[i]);
	}
	for (int i = 0; i < objItem.size(); i++)
	{
		objItem[i]->SetPosition(itemPos[i]);
		objItem[i]->SetRotation({ 90,0,0 });
		miniMapItem[i]->SetPosition(miniMapItemPos[i]);
	}

	//スコアかんり
	if (!Sprite::LoadTexture(3, L"Resources/text.png")) {
		assert(0);
		return;
	}
	spriteText.Initialize(3);
	scorePos = { 1650,200 };
	item = Sprite::Create(16,scorePos);
	item->SetSize({ 100,100 });
	itemCount = 0;
	mnitemCount = 0;
	score = 0;
	highscore = 0;
	scoreCount = 0;
	spriteScore = Sprite::Create(61,{1400, 100});
	X = Sprite::Create(60, { scorePos.x +135,scorePos.y+15 });
	X->SetSize({ 70,70 });
	for (int i = 0; i < 10; i++)
	{
		scorePng[i] = Sprite::Create(50 + i, { scorePos.x + 200,scorePos.y+15 });
		scorePng[i]->SetSize({70,70});
	}
	lastScorePos = { -80,850 };
	highScorePos = { 0,650 };
	lastScore = Sprite::Create(40,lastScorePos);
	highScore = Sprite::Create(62,highScorePos);
	//エネルギー管理

	 timeCount=0;
	 En=100;
	 mnEn = 0;
	 EnPos = { 1560,400 };
	 for (int i = 0; i < 10; i++)
	 {
		 Energy[i] = Sprite::Create(20 + i,  EnPos );
		 Energy[i]->SetSize({350,175});
	 }
	 monoEn = Sprite::Create(30, EnPos);
	 monoEn->SetSize({ 350, 175 });
	 spriteEn = Sprite::Create(41,{1430,300});
	//シーン管理
	sceneNumber = 0;
	gameOverPos = { 0,-100 };
	gameOverVelo = { 0,0 };
	gameOver = Sprite::Create(17,gameOverPos);
	boundCount = 0;
	BottomFlg = false;
	
	for (int i = 0; i < 9; i++)
	{
		gameClear[i] = Sprite::Create(31 + i, { 30,-290 });
		gameClearPos[i] = { 0,-290 };
		gameClear[i]->SetPosition(gameClearPos[i]);
	}
	clearCounter = 0;
	moveClearNum = 0;
	
	three = Sprite::Create(53, { 600,300 });
	two = Sprite::Create(52, { 600,300 });
	one = Sprite::Create(51, { 600,300 });
	startCounter = 0;
	rnd_pos = 0;
	pos = { 0,0 };
	heal = Sprite::Create(63, { 800,800 });
	healCount = 0;
	healTri = false;
	titlekun = Object3d::Create();
	titlekun->SetModel(modelPlayer);
	audio->Initialize();
	BGMcounter = 0;
	gageCounter = 0;
	left = Sprite::Create(64, { 500,430 });
	right = Sprite::Create(65, { 900,430 });
}




void GameScene::Update()
{
	if (BGMcounter == 0)
	{
		audio->PlayWave("Resources/bgm4.wav");
	}
	BGMcounter += 1;
	if (BGMcounter == 890)
	{
		BGMcounter = 0;
	}
	if (sceneNumber == 3)
	{
		ClearScene();
	}
	if (sceneNumber == 2)
	{
		GameOverScene();
	}
	if (sceneNumber == 1)
	{
		PlayScene();
	}
	if (sceneNumber == 0)
	{
		StartScene();
	}
	
	
	

	

	
	

	
		

}
void TitleUpdate(Object3d* objFighter, Input* input);
void GameScene::StartScene()
{

	mouPo.x = input->GetMousePosition().x;
	mouPo.y = input->GetMousePosition().y;
	center.x = 1535 / 2;
	center.y = 840 / 2;
	
	mouMo.x = mouPo.x - center.x;
	mouMo.y = mouPo.y - center.y;
	

	TitleUpdate(titlekun,input);


	if(Vector2::DistanceAtoB(mouPo, center) > dZone)
	{

	}
	else
	{
		if (input->IsLeftClick() == true)
		{
			sceneNumber += 1;
	  }
	}
}
void GameScene::PlayScene()
{
	if (healTri == true)
	{
		healCount++;
		if (healCount > 60)
		{
			healTri = false;
			healCount = 0;
		}
	}
	if (startCounter == 0)
	{
		audio->PlayWave("Resources/startHorn.wav");
	}
	startCounter += 1;
	start = startCounter;
	if (startCounter <= 180)
	{
	
		objGoal->SetScale({ scale,scaleY,scale });
		objGoal->Update();
		PlayerUpdate(playerObj, input);
		for (int i = 0; i < objFloor.size(); i++)
		{
			objFloor[i]->SetScale({ scale, scaleY, scale });
			objFloor[i]->Update();

		}
		for (int i = 0; i < objWall.size(); i++)
		{
			objWall[i]->SetScale({ scale,scaleY,scale });
			objWall[i]->Update();
		}
		for (int i = 0; i < objItem.size(); i++)
		{
			objItem[i]->SetScale({ 3,3,3 });
			objItem[i]->SetRotation(itemRot);
			objItem[i]->Update();
		}
		for (int i = 0; i < floorPos.size(); i++)
		{
			floorCol.Set(floorPos[i], floorSize*scale / 2, floorSize*scale / 2);
			if (BogusBoxCollision::IsHitAtoB(playerCol, floorCol) == true)
			{
				miniMapPlayerPos = XMFLOAT2{ miniMapPos.x + miniMapChipX * -x[i] + miniMapSize.x,miniMapPos.y + miniMapChipZ * z[i] };
			}
		}

		miniMapPlayer->SetPosition(miniMapPlayerPos);
		miniMapPlayer->SetSize(XMFLOAT2{ miniMapChipXsize,miniMapChipZsize });
		for (int i = 0; i < miniMapItem.size(); i++)
		{
			miniMapItem[i]->SetSize(XMFLOAT2{ miniMapChipXsize,miniMapChipZsize });
		}



	}
	if (startCounter > 180)
	{
	
		PlayerUpdate(playerObj, input);
		objGoal->SetScale({ scale,scaleY,scale });
		objGoal->Update();
		for (int i = 0; i < objFloor.size(); i++)
		{
			objFloor[i]->SetScale({ scale, scaleY, scale });
			objFloor[i]->Update();

		}
		for (int i = 0; i < objWall.size(); i++)
		{
			objWall[i]->SetScale({ scale,scaleY,scale });
			objWall[i]->Update();
		}
		itemRot.y = itemRot.y + 1;
		for (int i = 0; i < objItem.size(); i++)
		{
			objItem[i]->SetScale({ 3,3,3 });
			objItem[i]->SetRotation(itemRot);
			objItem[i]->Update();
		}

		//当たり判定
		for (int i = 0; i < wallPos.size(); i++)
		{
			wallCol.Set(wallPos[i], floorSize*scale / 2, floorSize*scale / 2);
			if (BogusBoxCollision::IsHitAtoB(playerCol, wallCol) == true)
			{
				sceneNumber = 2;
				audio->PlayWave("Resources/gameOver.wav");
			}
		}
		for (int i = 0; i < itemPos.size(); i++)
		{
			itemCol.Set(itemPos[i], 3, 3);
			if (BogusBoxCollision::IsHitAtoB(playerCol, itemCol) == true)
			{
				if (getItemNum[i] == false)
				{
					itemCount++;
					En += 10;
					audio->PlayWave("Resources/getItem.wav");
					getItemNum[i] = true;
					healTri = true;
				}
			}
		}
		if (playerPos.y <= -floorSize * scaleY / 2)
		{

			sceneNumber = 2;
		}
		goalCol.Set(goalPos, floorSize*scale / 2, floorSize*scale / 2);
		if (BogusBoxCollision::IsHitAtoB(playerCol, goalCol) == true)
		{
			sceneNumber = 3;
			audio->PlayWave("Resources/hakusyu2.wav");

		}


		//ミニマップ管理
		for (int i = 0; i < floorPos.size(); i++)
		{
			floorCol.Set(floorPos[i], floorSize*scale / 2, floorSize*scale / 2);
			if (BogusBoxCollision::IsHitAtoB(playerCol, floorCol) == true)
			{
				miniMapPlayerPos = XMFLOAT2{ miniMapPos.x + miniMapChipX * -x[i] + miniMapSize.x,miniMapPos.y + miniMapChipZ * z[i] };
			}
		}

		miniMapPlayer->SetPosition(miniMapPlayerPos);
		miniMapPlayer->SetSize(XMFLOAT2{ miniMapChipXsize,miniMapChipZsize });
		for (int i = 0; i < miniMapItem.size(); i++)
		{
			miniMapItem[i]->SetSize(XMFLOAT2{ miniMapChipXsize,miniMapChipZsize });
		}




		//エネルギー管理
		if (En < 70)
		{
			rnd_pos = 0.5f;
		}
		if (En < 50)
		{
			rnd_pos = 1.0f;
		}
		if (En < 30)
		{
			rnd_pos = 1.5f;
		}
		if (En < 10)
		{
			rnd_pos = 3.0f;
		}
		pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		//エネルギー用カウンター
		timeCount++;
		if (timeCount >= 30)
		{
			timeCount = 0;
			En -= 1;
		}
		if (En <= 0)
		{
			sceneNumber = 2;
		}
		
		
			EnPos.x += pos.x;
			EnPos.y += pos.y;
		
		for (int i = 0; i < 10; i++)
		{
			Energy[i]->SetPosition(EnPos);
		}
		monoEn->SetPosition(EnPos);
	}
}
void GameScene::GameOverScene()
{
	
	mouPo.x = input->GetMousePosition().x;
	mouPo.y = input->GetMousePosition().y;

	gameOverVelo.y +=0.2*(boundCount+1);	
	if (gameOverPos.y > 270)
	{
		boundCount += 1;
		if (boundCount < 4)
		{
			gameOverVelo.y = -(10-boundCount);			
		}
	}
	if (boundCount >= 4)
	{
		gameOverVelo.y = 0;
		Bottom->SetPosition({ 1200, 800 });
		BottomFlg = true;
	}
	gameOverPos.y += gameOverVelo.y;
	gameOver->SetPosition(gameOverPos);
	for (int i = 0; i < objFloor.size(); i++)
	{
		objFloor[i]->SetScale({ scale, scaleY, scale });
		objFloor[i]->Update();

	}
	for (int i = 0; i < objWall.size(); i++)
	{
		objWall[i]->SetScale({ scale,scaleY,scale });
		objWall[i]->Update();
	}
	for (int i = 0; i < objItem.size(); i++)
	{

		objItem[i]->Update();
	}
	for (int i = 0; i < floorPos.size(); i++)
	{
		floorCol.Set(floorPos[i], floorSize*scale / 2, floorSize*scale / 2);
		if (BogusBoxCollision::IsHitAtoB(playerCol, floorCol) == true)
		{
			miniMapPlayerPos = XMFLOAT2{ miniMapPos.x + miniMapChipX * -x[i] + miniMapSize.x,miniMapPos.y + miniMapChipZ * z[i] };
		}
	}

	miniMapPlayer->SetPosition(miniMapPlayerPos);
	miniMapPlayer->SetSize(XMFLOAT2{ miniMapChipXsize,miniMapChipZsize });
	for (int i = 0; i < miniMapItem.size(); i++)
	{
		miniMapItem[i]->SetSize(XMFLOAT2{ miniMapChipXsize,miniMapChipZsize });
	}

	center.x = 1010.0f;
	center.y = 640.0f;
	if (BottomFlg == true)
	{

		if (Vector2::DistanceAtoB(mouPo, center) > dZone)
		{

		}
		else
		{

			if (input->IsLeftClick() == true)
			{
				
				gameLoop();
			}

		}
	}

	
}
void GameScene::ClearScene()
{
	mouPo.x = input->GetMousePosition().x;
	mouPo.y = input->GetMousePosition().y;
	
	


	score = mnitemCount * 100000 + mnEn * 100;

	clearCounter++;
	gameClearPos[moveClearNum].y += 510 / 20;
	gameClear[moveClearNum]->SetPosition(gameClearPos[moveClearNum]);
	if (clearCounter >= 20 && moveClearNum < 8)
	{
		moveClearNum += 1;
		clearCounter = 0;
	}

	if (moveClearNum == 8 && clearCounter > 60)
	{
		scoreCount++;
		if (scoreCount >= 60)
		{
			if (itemCount > 0)
			{
				itemCount -= 1;
				mnitemCount += 1;
				scoreCount = 0;
				audio->PlayWave("Resources/getItem.wav");
				if (itemCount == 0)
				{
					scoreCount = -60;
				}
			}


		}
		
		if (En >= 0 && scoreCount >= 3 && itemCount == 0)
		{
			En -= 1;
			mnEn += 1;
			scoreCount = 0;
			gageCounter++;
		
			if (gageCounter > 3)
			{
				audio->PlayWave("Resources/getscore.wav");
				gageCounter = 0;
			}
		}
		if (En <= 0 && scoreCount > 120)
		{
			Bottom->SetPosition({ 1200, 800	});
			BottomFlg = true;
		}
	}
	
	
	for (int i = 0; i < objFloor.size(); i++)
	{
		objFloor[i]->SetScale({ scale, scaleY, scale });
		objFloor[i]->Update();

	}
	for (int i = 0; i < objWall.size(); i++)
	{
		objWall[i]->SetScale({ scale,scaleY,scale });
		objWall[i]->Update();
	}
	for (int i = 0; i < objItem.size(); i++)
	{

		objItem[i]->Update();
	}
	for (int i = 0; i < floorPos.size(); i++)
	{
		floorCol.Set(floorPos[i], floorSize*scale / 2, floorSize*scale / 2);
		if (BogusBoxCollision::IsHitAtoB(playerCol, floorCol) == true)
		{
			miniMapPlayerPos = XMFLOAT2{ miniMapPos.x + miniMapChipX * -x[i] + miniMapSize.x,miniMapPos.y + miniMapChipZ * z[i] };
		}
	}

	miniMapPlayer->SetPosition(miniMapPlayerPos);
	miniMapPlayer->SetSize(XMFLOAT2{ miniMapChipXsize,miniMapChipZsize });
	for (int i = 0; i < miniMapItem.size(); i++)
	{
		miniMapItem[i]->SetSize(XMFLOAT2{ miniMapChipXsize,miniMapChipZsize});
	}
	scorePos = { 730,790 };
	item->SetPosition(scorePos);
	X->SetPosition({ scorePos.x + 135,scorePos.y + 15 });

	for (int i = 0; i < 10; i++)
	{
		scorePng[i]->SetPosition({ scorePos.x + 200,scorePos.y + 15 });

	}
	EnPos = { 670,910 };
	for (int i = 0; i < 10; i++)
	{
		Energy[i]->SetPosition(EnPos);
		
	}
	monoEn->SetPosition(EnPos);

	string aa = to_string(score);
	string bb = to_string(highscore);
	spriteText.Print(aa,lastScorePos.x+400,lastScorePos.y+20,5);
	spriteText.Print(bb, highScorePos.x + 500, highScorePos.y+20, 5);
	center.x = 1010.0f;
	center.y = 640.0f;
	if (BottomFlg == true)
	{

		if (Vector2::DistanceAtoB(mouPo, center) > dZone)
		{
			
		}
		else
		{

			if (input->IsLeftClick() == true)
			{
				if (highscore < score)
				{
					highscore = score;
				}
				gameLoop();
			}

		}
	}
}





void GameScene::Draw()
{
	if (sceneNumber == 3)
	{
		ClearDraw();
	}
	if (sceneNumber == 2)
	{
		GameOverDraw();
	}
	if (sceneNumber == 1)
	{
		PlayDraw();
	}
	if (sceneNumber == 0)
	{
		StartDraw();
	}
	
	
	
}
void GameScene::StartDraw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	startScreen->Draw();
	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);

	// 3Dオブクジェクトの描画
	
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	titlekun->Draw();
	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	//// 描画
	title->Draw();
	Bottom->Draw();

	// デバッグテキストの描画
	debugText.DrawAll(cmdList);
	spriteText.DrawAll(cmdList);
	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}





//ゲームシーン
void GameScene::PlayDraw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	
	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	BG->Draw();
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);

	// 3Dオブクジェクトの描画

	//マップチップ
	for (int i = 0; i < objFloor.size(); i++)
	{
		objFloor[i]->Draw();
	}
	for (int i = 0; i < objWall.size(); i++)
	{
		objWall[i]->Draw();

	}

	for (int i = 0; i < objItem.size(); i++)
	{
		if (getItemNum[i] == false)
		{
			objItem[i]->Draw();
		}

	}
	objGoal->Draw();
	playerObj->Draw();
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	//// 描画
	
	miniMap->Draw();
	for (int i = 0; i < miniMapItemPos.size(); i++)
	{
		if (getItemNum[i] == false)
		{
			miniMapItem[i]->Draw();
		}
	}
	miniMapGoal->Draw();
	miniMapPlayer->Draw();
	item->Draw();
	monoEn->Draw();
	spriteScore->Draw();
	spriteEn->Draw();
	X->Draw();
	scorePng[itemCount]->Draw();
	if (En > 90)
	{
		for (int i = 0; i < 10; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if(En>80)
	{
		for (int i = 0; i < 9; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 70)
	{
		for (int i = 0; i <8; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 60)
	{
		for (int i = 0; i < 7; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 50)
	{
		for (int i = 0; i < 6; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 40)
	{
		for (int i = 0; i < 5; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 30)
	{
		for (int i = 0; i < 4; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 20)
	{
		for (int i = 0; i < 3; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 10)
	{
		for (int i = 0; i < 2; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 0)
	{
		for (int i = 0; i < 1; i++)
		{
			Energy[i]->Draw();
		}
	}
	if (startCounter >= 0 && startCounter <= 60)
	{
		three->Draw();
		left->Draw();
		right->Draw();
	}
	if (startCounter >= 61 && startCounter <= 120)
	{
		two->Draw();
		left->Draw();
		right->Draw();
	}
	if (startCounter >= 121 && startCounter <= 180)
	{
		one->Draw();
		left->Draw();
		right->Draw();
	}
	if (healTri == true)
	{
		heal->Draw();
	}
	// デバッグテキストの描画
	debugText.DrawAll(cmdList);
	spriteText.DrawAll(cmdList);
	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}






void GameScene::GameOverDraw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	
	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	BG->Draw();
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);

	// 3Dオブクジェクトの描画

	//マップチップ
	for (int i = 0; i < objFloor.size(); i++)
	{
		objFloor[i]->Draw();
	}
	for (int i = 0; i < objWall.size(); i++)
	{
		objWall[i]->Draw();

	}
	for (int i = 0; i < objItem.size(); i++)
	{
		if (getItemNum[i] == false)
		{
			objItem[i]->Draw();
		}

	}
	objGoal->Draw();
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	//// 描画
	
	miniMap->Draw();
	for (int i = 0; i < miniMapItemPos.size(); i++)
	{
		if (getItemNum[i] == false)
		{
			miniMapItem[i]->Draw();
		}
	}
	miniMapGoal->Draw();
	miniMapPlayer->Draw();
	item->Draw();
	monoEn->Draw();
	if (En > 90)
	{
		for (int i = 0; i < 10; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 80)
	{
		for (int i = 0; i < 9; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 70)
	{
		for (int i = 0; i < 8; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 60)
	{
		for (int i = 0; i < 7; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 50)
	{
		for (int i = 0; i < 6; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 40)
	{
		for (int i = 0; i < 5; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 30)
	{
		for (int i = 0; i < 4; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 20)
	{
		for (int i = 0; i < 3; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 10)
	{
		for (int i = 0; i < 2; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 0)
	{
		for (int i = 0; i < 1; i++)
		{
			Energy[i]->Draw();
		}
	}
	X->Draw();
	scorePng[itemCount]->Draw();
	spriteScore->Draw();
	spriteEn->Draw();
	gameOver->Draw();
	if (BottomFlg == true)
	{
		Bottom->Draw();
	}
	// デバッグテキストの描画
	debugText.DrawAll(cmdList);
	spriteText.DrawAll(cmdList);
	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}








void GameScene::ClearDraw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);

	// 3Dオブクジェクトの描画

	//マップチップ
	/*for (int i = 0; i < objFloor.size(); i++)
	{
		objFloor[i]->Draw();
	}
	for (int i = 0; i < objWall.size(); i++)
	{
		objWall[i]->Draw();

	}
	for (int i = 0; i < objItem.size(); i++)
	{
		if (getItemNum[i] == false)
		{
			objItem[i]->Draw();
		}

	}
	objGoal->Draw();*/
	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	//// 描画
	
	//miniMap->Draw();
	/*for (int i = 0; i < miniMapItemPos.size(); i++)
	{
		if (getItemNum[i] == false)
		{
			miniMapItem[i]->Draw();
		}
	}
	miniMapGoal->Draw();
	miniMapPlayer->Draw();*/
	BG->Draw();
	item->Draw();
	monoEn->Draw();
	if (En > 90)
	{
		for (int i = 0; i < 10; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 80)
	{
		for (int i = 0; i < 9; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 70)
	{
		for (int i = 0; i < 8; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 60)
	{
		for (int i = 0; i < 7; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 50)
	{
		for (int i = 0; i < 6; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 40)
	{
		for (int i = 0; i < 5; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 30)
	{
		for (int i = 0; i < 4; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 20)
	{
		for (int i = 0; i < 3; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 10)
	{
		for (int i = 0; i < 2; i++)
		{
			Energy[i]->Draw();
		}
	}
	else if (En > 0)
	{
		for (int i = 0; i < 1; i++)
		{
			Energy[i]->Draw();
		}
	}
	X->Draw();
	scorePng[itemCount]->Draw();
	/*spriteScore->Draw();
	spriteEn->Draw();*/
	lastScore->Draw();
	highScore->Draw();
	for (int i = 0; i < 9; i++)
	{
		gameClear[i]->Draw();
	}
	if (BottomFlg == true)
	{
		Bottom->Draw();
	}
	// デバッグテキストの描画
	debugText.DrawAll(cmdList);
	spriteText.DrawAll(cmdList);
	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}
void PlayerUpdate(Object3d* objFighter, Input* input) {
	Vector2 preMou = mouPo;
	playerPos = objFighter->GetPosition();
	cameraPos = Object3d::GetEye();
    cameraTergetPos = Object3d::GetTarget();
	center.x = 1535 / 2;
	center.y = 840 / 2;

	mouPo.x = input->GetMousePosition().x;
	mouPo.y = input->GetMousePosition().y;
	mouMo.x = preMou.x - mouPo.x;
	mouMo.y = preMou.y - mouPo.y;

	playerCol.Set(playerPos, 1.0f, 2.0f);

	XMFLOAT3 gRot(0.0f, 0.0f, 0.0f);

	objFighter->SetBillboard(1);

	// カメラ移動
	if (mouMo.x > dZone || mouMo.x < -dZone)
	{

		if (mouMo.x > -dZone) {
			gRot = { -20.0f, 10.0f, 0.0f };
		}

		if (mouMo.x < dZone) {
			gRot = { -20.0f, -10.0f, 0.0f };
		}

	/*	if (mouMo.y < -dZone) {
			gRot = { -40.0f, 0.0f, 0.0f };
		}

		if (mouMo.y > dZone) {
			gRot = { -10.0f, 0.0f, 0.0f };
		}*/

		angleXZ += mouMo.x * 0.0002f;
		/*angleYZ += mouMo.y * 0.0003f;*/
	}
	else
	{
		gRot = { -20.0f, 0.0f, 0.0f };
	}

	objFighter->SetRotation(gRot);

	if (angleXZ > 6.28319) {
		angleXZ = 0;
	}

	if (angleYZ < -1.0473f || angleYZ > 1.0473f) {
		if (angleYZ < -0.785398f) { angleYZ = -1.0472f; }
		else if (angleYZ > 0.785398f) { angleYZ = 1.0472f; }
	}

	cameraPos.x = cameraDistance * sinf(angleXZ);
	cameraPos.z = cameraDistance * cosf(angleXZ);
	cameraPos.y = cameraDistance * sinf(angleYZ);
	cameraPos.x += playerPos.x;
	cameraPos.y += playerPos.y + 6.0f;
	cameraPos.z += playerPos.z;

	playerDirec.x = cameraDistance * sinf(angleXZ + pi);
	playerDirec.y = cameraDistance * sinf(angleYZ + pi);
	playerDirec.z = cameraDistance * cosf(angleXZ + pi);
	playerDirec.Nomalize();
	playerVel = playerDirec;
	playerVel *= 0.45f;

	if(start>180)
	{ 
	playerPos.x += playerVel.x;
	playerPos.y += playerVel.y;
	playerPos.z += playerVel.z;
	}
	cameraTergetPos = playerPos;
	cameraTergetPos.y += 2.0f;


	Object3d::SetEye(cameraPos);
	Object3d::SetTarget(cameraTergetPos);
	objFighter->SetPosition(playerPos);
	objFighter->Update();
	
}



void GameScene::gameLoop()
{

	angleXZ = 0.0f;
	angleYZ = 0.0f;
	center.x = 1535 / 2;
	center.y = 840 / 2;
	playerVel = { 0.0f, 0.0f, 0.0f };
	playerDirec = { 0.0f, 0.0f, 0.0f };

	Bottom->SetPosition({ 1920 / 2 - 40,1080 / 2 });
	itemRot = { 90,0,0 };
	for (int zi = 0; zi < mapZcount; zi++)
	{
		for (int xi = 0; xi < mapXcount; xi++)
		{
			if (zi == 25 && xi == 12)
			{
				playerObj->SetPosition({ xi*floorSize*scale,0,zi*floorSize*scale });
				miniMapPlayerPos = XMFLOAT2{ miniMapPos.x + miniMapChipX * -xi + miniMapSize.x,miniMapPos.y + miniMapChipZ * zi };
			}
		}
	}
	scorePos = { 1650,200 };
	item->SetPosition(scorePos);
	itemCount = 0;
	mnitemCount = 0;
	score = 0;
	scoreCount = 0;
	X->SetPosition( { scorePos.x + 135,scorePos.y + 15 });
	for (int i = 0; i < 10; i++)
	{
		scorePng[i]->SetPosition( { scorePos.x + 200,scorePos.y + 15 });
		
	}
	timeCount = 0;
	En = 100;
	mnEn = 0;
	EnPos = { 1560,400 };
	for (int i = 0; i < 10; i++)
	{
		Energy[i]->SetPosition(EnPos);
	
	}
	monoEn->SetPosition(EnPos);
	sceneNumber = 0;
	gameOverPos = { 0,-100 };
	gameOverVelo = { 0,0 };
	gameOver->SetPosition(gameOverPos);
	boundCount = 0;
	BottomFlg = false;
	for (int i = 0; i < 9; i++)
	{
		gameClearPos[i] = { 0,-290 };
		gameClear[i]->SetPosition(gameClearPos[i]);
	}
	clearCounter = 0;
	moveClearNum = 0;
	for (int i = 0; i < getItemNum.size(); i++)
	{
		getItemNum[i] = false;
	}
	startCounter = 0;
	start = 0;
	rnd_pos = 0;
	pos = { 0,0 };
	healCount = 0;
	audio->Initialize();
	BGMcounter = 0;
	gageCounter = 0;
}
void TitleUpdate(Object3d* objFighter, Input* input) {
	XMFLOAT3 playerPos = objFighter->GetPosition();
	XMFLOAT3 cameraPos = Object3d::GetEye();
	XMFLOAT3 cameraTergetPos = Object3d::GetTarget();
	static XMFLOAT3 gRot = { 0,0,0 };
	/*center.x = 1260 / 2;
	center.y = 720 / 2;

	mouPo.x = input->GetMousePosition().x;
	mouPo.y = input->GetMousePosition().y;
	mouMo.x = mouPo.x - center.x;
	mouMo.y = mouPo.y - center.y;*/
	playerPos = { 0.0f, 100.0f, 0.0f };
	objFighter->SetPosition(playerPos);

	objFighter->SetBillboard(1);

	gRot.y = 230;
	gRot.x = 0;
	gRot.z += 0.5f;
	//gRot.z += 0.5f;
	if (gRot.z > 360) {
		gRot.z = 0;
	}

	objFighter->SetScale({ 2.0f,2.0f,2.0f });

	objFighter->SetRotation(gRot);

	cameraPos.x = cameraDistance * sinf(0);
	cameraPos.z = cameraDistance * cosf(0);
	cameraPos.y = cameraDistance * sinf(0);
	cameraPos.x += playerPos.x;
	cameraPos.y += playerPos.y + 4.0f;
	cameraPos.z += playerPos.z;

	cameraTergetPos = playerPos;
	cameraTergetPos.x += 2.5f;


	Object3d::SetEye(cameraPos);
	Object3d::SetTarget(cameraTergetPos);
	objFighter->Update();
}