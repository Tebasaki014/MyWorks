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
	//�����o�ϐ�
	Actor2D* spr = nullptr;
};