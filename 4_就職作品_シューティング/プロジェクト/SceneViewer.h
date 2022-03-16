#pragma once
#include"CommonData.h"
#include"Player.h"
#include"Enemy.h"
#include"Gage.h"
#include"Collision.h"
#include"Primitive.h"

class SceneViewer;
struct CommonData;

//シーン基底クラス
class Scene
{
public:
	Scene(CommonData* commonData, SceneViewer* viewer);
	~Scene() = default;
	void ChangeScene(Scene* pNewScene);

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void End() = 0;
protected:
	CommonData* commonData = nullptr;
	SceneViewer* viewer = nullptr;
	WatashiEngine* wangine = nullptr;
	Input* input = nullptr;
	Camera* camera = nullptr;
};

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

//シーン切り替えクラス
class SceneViewer
{
public:
	SceneViewer();
	~SceneViewer();

	void ChangeScene(Scene* pNewScene);

	void Initialize();
	void End();

	void Update();
	bool Draw();
	
private:

	CommonData* commonData = nullptr;
	Scene* nowScene = nullptr;
};

class TitleScene : public Scene
{
public:
	using Scene::Scene;

	void Start() override;
	void Update() override;
	void Draw() override;
	void End() override;

private:
	//メンバ変数
	Actor2D* spr = nullptr;
};

class ClearScene : public Scene
{
public:
	using Scene::Scene;

	void Start() override;
	void Update() override;
	void Draw() override;
	void End() override;

private:
	//メンバ変数
	Actor2D* spr = nullptr;
};

class OverScene : public Scene
{
public:
	using Scene::Scene;

	void Start() override;
	void Update() override;
	void Draw() override;
	void End() override;

private:
	//メンバ変数
	Actor2D* spr = nullptr;
};