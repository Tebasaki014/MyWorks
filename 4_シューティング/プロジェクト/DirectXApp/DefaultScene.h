#pragma once
#include"Scene.h"
#include"Player.h"
#include"Enemy.h"
#include"Gage.h"

//�V�[���N���X
class DefaultScene : public Scene
{
public:
	//�p���R���X�g���N�^(���N���X�̃R���X�g���N�^�𒼐ڌĂ�)
	using Scene::Scene;

	//����4���I�[�o�[���C�h
	void Start() override;
	void Update() override;
	void Draw() override;
	void End() override;

private:
	//�����o�ϐ�
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