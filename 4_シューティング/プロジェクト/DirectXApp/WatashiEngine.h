#pragma once
#include<ctime>
#include<random>

#include"SDelete.h"
#include"Input.h"
#include"Dx12App.h"
#include"FrameRate.h"
#include"Sprite.h"
#include"Object3D.h"
#include"ParticleManager.h"
#include"Audio.h"


#include"Vector2.h"
#include"Vector3.h"
#include"Quaternion.h"

class WatashiEngine
{
public:
	// いろいろ
	WinApp* win = nullptr;
	Dx12App* dx12 = nullptr;
	FrameRate* framerate = nullptr;
	Input* input = nullptr;
	Camera* camera = nullptr;
	bool IsUse2D = true;
	bool IsUse3D = true;

	//初期化
	void Initialize();
	//画面クリア
	bool ScreenClear(Color clearColor);
	//バッファ切り替え
	void ScreenFlip();
	//おわおわおわり
	void End();

	//サウンド
	//再生
	void PlayWav(const char* filename);

	//ウィンドウサイズ取得
	Vector2 GetWindowSize();

	//スプライト
	//描画開始
	void StartDraw2D();
	//描画終了
	void EndDraw2D();

	//モデル
	//描画開始
	void StartDraw3D();
	//描画終了
	void EndDraw3D();
};