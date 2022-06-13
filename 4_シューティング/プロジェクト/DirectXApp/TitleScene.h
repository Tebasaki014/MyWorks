#pragma once
#include"Scene.h"

class Scene;

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