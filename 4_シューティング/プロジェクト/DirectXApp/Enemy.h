#pragma once
#include"Player.h"
#include"CommonData.h"

class Enemy;

enum class D_State : unsigned short
{
	AboutJust,
	Near,
	Far,
	OutRange
};

class Move
{
public:
	Move(Enemy* enemy) { this->enemy = enemy; }
	virtual void Start(){}
	virtual void Update() = 0;
	virtual void End(){}
	virtual void Next(Move* newMove);

protected:
	Enemy* enemy = nullptr;
};

class Enemy : public Actor3D
{
public:
	using Actor3D::Actor3D;

	void Start() override;
	void Update() override;
	void Draw(const Shader& shader) override;
	void End() override;

	bool Look();

	void MeasureToPlayer();
	void shootBullet();
	void shootMissile();
	void bulletUpdate();
	void shootExplobe();

	void SetNewMove(Move* newMove);

	void SetCommon(CommonData* common) {
		comd = common;
	}

	void SetPlayer(Player* player) {
		this->player = player;
	}

	void Damage(int damage);

	Sphere* GetCollision() {
		return collision;
	}

	int GetHP() {
		return HP;
	}

	bool InPlayerSite();

	D_State distancetop = D_State::OutRange;

	Vector3 velocity = {};
	Quaternion look = Quaternion::Identity();

	Explosion* explosion = nullptr;

	bool isDead = false;

private:
	Move* nowMove = nullptr;

	CommonData* comd = nullptr;
	Player* player = nullptr;
	

	float moveSpeed = 0.0f;
	float dashSpeed = 0.0f;

	int cont = 0;

	float distanceToPlayer = 0.0f;
	Vector3 toPlayer = {};
	Vector3 target = {};
	
	Vector3 dashdir = {};

	std::vector<Bullet*> bullets;
	std::vector<Homing*> homings;
	
	float range = 100.0f;
	float farest = 50.0f;
	float nearest = 10.0f;
	float bulletspeed = 4.0f;
	float missilespeed = 1.5f;
	Sphere* collision = nullptr;
	Ray* ray = nullptr;

	Model* bumodel = nullptr;
	Model* maru = nullptr;

	float expRate = 0.1f;
	Vector3 expScale = { 10.0f,10.0f,10.0f };

	int HP = 50;

	ParticleEmitter* mslExp = nullptr;
};

#pragma region Moves
class Blank : public Move
{
public:
	using Move::Move;

	void Update() override;

private:
	int count = 0;
};

class Dash : public Move
{
public:
	using Move::Move;

	void Start() override;
	void Update() override;

private:
	Vector3 direction = {};
	float speed = 0.0f;
	int repeat = 3;
	int count = 0;
	bool isStep = false;
};

class Attack : public Move
{
public:
	using Move::Move;

	void Update() override;

private:
	int count = 0;
};

class Shoot : public Move
{
public:
	using Move::Move;

	void Update() override;

private:
	int count = 0;
	int shooted = 0;
	int repeat = 3;
	int interval = 10;
};

class Missile : public Move
{
public:
	using Move::Move;

	void Update() override;

private:
	int count = 0;
	int shooted = 0;
	int repeat = 6;
	std::vector<Vector3> positions;
};

class Boom : public Move
{
public:
	using Move::Move;

	void Start() override;
	void Update() override;
	void End() override;

private:

};
#pragma endregion