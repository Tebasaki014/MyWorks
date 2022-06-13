#pragma once
#include"Scene.h"
#include"Player.h"
#include"Enemy.h"
#include"Gage.h"

//シーンクラス
class DefaultScene : public Scene
{
public:
	//継承コンストラクタ(基底クラスのコンストラクタを直接呼ぶ)
	using Scene::Scene;

	//この4つをオーバーライド
	void Start() override;
	void Update() override;
	void Draw() override;
	void End() override;

private:
	//メンバ変数
	Actor2D* spr = nullptr;
	Actor3D* ground = nullptr;
	Actor3D* sky = nullptr;
	Player* player = nullptr;
	Enemy* enemy = nullptr;

	Shader* toon = nullptr;
	Shader* phong = nullptr;
	Shader* basic = nullptr;

	Vector3 lightDir = { 0, 1, -1 };
	float lightRotAngle = 0.0002f;

	ParticleEmitter* ppp = nullptr;

	CircleGage2D* gage = nullptr;
	CircleGage2D* pgage = nullptr;
};