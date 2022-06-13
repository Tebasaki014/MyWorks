#pragma once
#include "Actor.h"
#include"Collision.h"

class Bullet : public Actor3D
{
public:
	using Actor3D::Actor3D;

	void Start(Vector3 start, Vector3 target, float accel);
	void Update() override;
	void End() override;

	Vector3 targetPos = {};
	Vector3 startPos = {};
	float accel = 1.0f;

	bool isShot = false;

	Sphere* GetCollision() {
		return &collision;
	}
private:
	Vector3 velocity = {};
	Sphere collision = Sphere(position, 0.5f);
};

class Homing : public Actor3D 
{
public:
	using Actor3D::Actor3D;

	enum class State {
		Stay,
		Up,
		Target
	};

	State state = State::Up;

	void Start(Vector3 start, Vector3 target, float accel);
	void Update() override;
	void End() override;

	void SetTarget(const Vector3& target) {
		targetPos = target;
	}

	void SetStayPos(const Vector3& po) {
		stayPos = po;
	}

	Vector3 targetPos = {};
	Vector3 startPos = {};
	float accel = 1.0f;

	bool isShot = false;

	Sphere* GetCollision() {
		return &collision;
	}
private:
	Vector3 velocity = {};
	Vector3 stayPos = {};
	float highest = 20.0f;
	int interval = 80;
	float hormigRate = 0.2f;
	Sphere collision = Sphere(position, 0.5f);
	int count = 0;

	ParticleEmitter* backfire = nullptr;
	Vector3 fireGravity = {};
};

class Explosion : public Actor3D
{
public:
	using Actor3D::Actor3D;

	void Start(Vector3 position, Vector3 maxScale, float scaleRate);
	void Update() override;
	void End() override;

	Sphere* GetCollision() {
		return &collision;
	}

	bool isExplobe = false;

private:
	Vector3 maxScale = {};
	float scaleRate = 0.0f;

	int count = 0;
	int interval = 120;

	Sphere collision = Sphere(position, Scale.x);
};

class Spike : Actor3D 
{
public:
	using Actor3D::Actor3D;

	//void Start(Vector3 position, Vector3 direction, float scale);
	//void Update() override;
	//void End() override;

	bool isActive = false;

private:

	Vector3 scale = { 1.0f,1.0f,1.0f };
	Vector3 direction = {};
	float speed = 1.0f;

	int count = 0;

	Sphere collision = Sphere(position, Scale.x);
};