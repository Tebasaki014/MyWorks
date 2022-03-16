#pragma once

#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "DebugText.h"
#include "Audio.h"
#include "CollisionPrimitive.h"
#include "FlameRate.h"
#include <vector>
#include"SpriteText.h"
#include "Vector3.h"
#include"Vector2.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene
{
	
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // 静的メンバ変数
	static const int debugTextTexNumber = 2;

public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();
	void StartScene();
	void PlayScene();
	void GameOverScene();
	void ClearScene();
	void gameLoop();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	void StartDraw();
	void PlayDraw();
	void GameOverDraw();
	void ClearDraw();

private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;	
	//スタートシーン用
	Sprite* startScreen;
	Sprite* title;
	Sprite* Bottom;
	

	XMFLOAT3 titlePos;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	Object3d* playerObj;
	Model* modelPlayer;

	

	// 当たり判定 球
	Sphere sphere;
	// 当たり判定 平面
	Plane plane;
	
	//マップチップ
	Model* modelFloor = nullptr;
	std::vector<Object3d*> objFloor;
	std::vector<XMFLOAT3> floorPos;
	Model* modelWall = nullptr;
	std::vector<Object3d*> objWall;
	std::vector<XMFLOAT3> wallPos;
	Model* modelItem = nullptr;
	std::vector<Object3d*> objItem;
	std::vector<XMFLOAT3> itemPos;
	std::vector<bool> getItemNum;
	XMFLOAT3 itemRot;
	Model* modelGoal;
	XMFLOAT3 goalPos;
	Object3d* objGoal;

	//ミニマップ
	XMFLOAT2 miniMapPos = { 1434, 596 };
	XMFLOAT2 miniMapSize = { 486,486 };
	float miniMapChipX;
	float miniMapChipZ;
	float miniMapChipXsize;
	float miniMapChipZsize;
	Sprite* miniMap;
	std::vector<Sprite*> miniMapItem;
	std::vector<XMFLOAT2> miniMapItemPos;
	Sprite* miniMapPlayer;
	XMFLOAT2 miniMapPlayerPos;
	Sprite* miniMapGoal;
	XMFLOAT2 miniMapGoalPos;
	float floorSize = 2;
	float scale = 6;
	float scaleZ = 3;
	float scaleY = 10;
	
	short floor[27][31] = {
	{1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1},
	{1,01, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,1},
	{1,1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,1},
	{1,1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0,1},
	{1,1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,1},
	{1,1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,1},
	{1,1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,1},
	{1,1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 2, 0, 1, 0, 0, 1, 0, 0, 1, 2, 0, 1, 0, 0,1},
	{1,1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,1},
	{1,1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,1},
	{1,1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0,1},
	{1,1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 2, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0,1},
	{1,1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,1},
	{1,1, 0, 0, 1, 0, 2, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,1},
	{1,0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,1},
	{1,0, 0, 2, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,1},
	{1,0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 0, 1, 0, 0, 1, 0, 0, 2, 0, 0, 3, 0,1},
	{1,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0,1},
	{1,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,1},
	{1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1},
	{1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1},
	{1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1},
	{1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1},
	{1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1},
	{1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1},
	{1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1},
	{1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1},
	};
	const short mapXcount = 31;
	const short mapZcount = 27;
    //スコア管理
	Sprite* spriteScore;
	Sprite* item;
	XMFLOAT2 scorePos;
	SpriteText spriteText;
	int score;
	short itemCount;
	short mnitemCount;
	short scoreCount;
	Sprite* scorePng[10];
	Sprite* X;
	Sprite* lastScore;
	XMFLOAT2 lastScorePos;
	Sprite* highScore;
	XMFLOAT2 highScorePos;
	int highscore;
	//ゲージ管理
	Sprite* spriteEn;
	Sprite* monoEn;
	Sprite* Energy[10];
	short timeCount;	
	float En;
	float mnEn;
	XMFLOAT2 EnPos;
	//背景
	Sprite* BG;
	//シーン管理
	short  sceneNumber;
	short boundCount;
	Sprite* gameOver;
	XMFLOAT2 gameOverPos;
	XMFLOAT2 gameOverVelo;
	Sprite*  gameClear[9];
	XMFLOAT2 gameClearPos[9];
	short clearCounter;
	short moveClearNum;
	bool BottomFlg;

	//スタートのとこ
	int startCounter;
	Sprite* three;
	Sprite* two;
	Sprite* one;
	 float rnd_pos = 0.5f;
	XMFLOAT2 pos;
	Sprite* heal;
	int healCount;
	bool healTri;
	Object3d* titlekun;
	short BGMcounter;
	short gageCounter;
	Sprite* left;
	Sprite* right;
};

