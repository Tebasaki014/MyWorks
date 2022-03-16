#pragma once
#include"Actor.h"
#include"CommonData.h"
#include"Bullet.h"
#include"Collision.h"

class Player : public Actor3D
{
public:
	using Actor3D::Actor3D;

	void Start() override;
	void Update() override;
	void End() override;
	void Draw(const Shader& shader) override;

	void shootBullet();
	void bulletUpdate();

	Vector3 CameraVivlate(float range);

	void SetCommon(CommonData* common) { 
		this->comd = common;
		this->cam = comd->wangine->camera;
		this->input = comd->wangine->input;
	}

	const Ray* GetRay() {
		return ray;
	}

	const Sphere* GetCollision() {
		return collision;
	}

	const std::vector<Bullet*> GetBullets() {
		return bullets;
	}

	const int GetHP() {
		return HP;
	}

	void Damage(int damage);

	Vector3 cameraTarget = {};

	bool isDead = false;

private:
	CommonData* comd = nullptr;
	Input* input = nullptr;
	Camera* cam = nullptr;

	Vector3 cameraFirstPos = {};
	Vector3 cameraPos = {};
	
	Vector3 cameraOffset = {};
	Vector3 cameraAngle = {};
	Vector3 cameraSpeed = {};
	float cameraDistance;
	float targetDistance;

	Vector3 playerVelocity = {};
	Vector3 playerMoveDirection = {};
	float moveAccel;
	float stepAccel;

	std::vector<Bullet*> bullets;
	float range = 100.0f;
	float bulletspeed = 4.0f;
	bool isStep = false;
	bool isVible = false;
	int vivrateFrame = 0;
	float vivrateRange = 0.0f;

	Ray* ray = nullptr;
	Sphere* collision = nullptr;

	Model* bbm = nullptr;

	int HP = 20;

	ParticleEmitter* boost = nullptr;
	ParticleEmitter* walk = nullptr;

	int count = 0;
};

class PostEffectModoki
{
public:
	PostEffectModoki();
	~PostEffectModoki() {
		SDelete(syuchu);
		SDelete(yokosyu);
	}

private:
	Sprite* syuchu = nullptr;
	Sprite* yokosyu = nullptr;

	float alpha = 1.0f;



	bool isSyuchu = false;
	bool isYokoShu = false;
};