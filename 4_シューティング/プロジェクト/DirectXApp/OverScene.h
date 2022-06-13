#pragma once
#include"Scene.h"

class Scene;

class OverScene : public Scene
{
public:
	using Scene::Scene;

	void Start() override;
	void Update() override;
	void Draw() override;
	void End() override;

private:
	//ƒƒ“ƒo•Ï”
	Actor2D* spr = nullptr;
};