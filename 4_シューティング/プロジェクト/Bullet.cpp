#include "Bullet.h"

void Bullet::Start(Vector3 start, Vector3 target, float accel)
{
	this->startPos = start;
	this->targetPos = target;
	this->accel = accel;

	position = startPos;
	Quaternion q = Quaternion::LookVector(targetPos - startPos);
	SetRotation(q);
	ModelUpdate();
	velocity = forwordAxis * accel;

	collision.position = position;
}

void Bullet::Update()
{
	if (isShot) {
		velocity = forwordAxis * accel;
		position += velocity;
		collision.position = position;
		ModelUpdate();
	}
}

void Bullet::End()
{
}

void Homing::Start(Vector3 start, Vector3 target, float accel)
{
	this->startPos = start;
	this->targetPos = target;
	this->accel = accel;

	position = startPos + (Vector3::WorldY() * 2);
	stayPos = startPos;
	Quaternion q = Quaternion::LookVector(Vector3::WorldY());
	SetRotation(q);
	ModelUpdate();
	velocity = forwordAxis * accel;

	state = State::Stay;
	collision.position = position;

	count = 0;
	
	Vector3 c(1.0f, 0.3f, 0.0f);
	backfire = new ParticleEmitter(10, position, 0.1f, 20, 0.8f, 0.1f, c, c);
	backfire->SetGravity(fireGravity);
}

void Homing::Update()
{
	if (isShot) {

		Quaternion look = Quaternion::LookVector(targetPos - position);
		fireGravity = {};

		switch (state)
		{
		case Homing::State::Stay:

			position = Vector3::Lerp(position, stayPos, 0.5f);


			if (count >= interval) {
				count = 0;
				state = State::Up;
			}
			count++;

			break;
		case Homing::State::Up:

			position += velocity;
			collision.position = position;
			if (position.y >= highest) {
				state = State::Target;
			}

			backfire->SetGravity(fireGravity);
			backfire->Live(position);
			break;
		case Homing::State::Target:
	
			SetRotation(Quaternion::SLerp(GetRotation(), look, hormigRate));
			velocity = forwordAxis * accel;
			position += velocity;
			collision.position = position;

			backfire->SetGravity(fireGravity);
			backfire->Live(position - forwordAxis);
			break;
		default:
			break;
		}

		ModelUpdate();
	}
}

void Homing::End()
{
	SDelete(backfire);
}

void Explosion::Start(Vector3 position, Vector3 maxScale, float scaleRate)
{
	this->position = position;
	this->maxScale = maxScale;
	this->scaleRate = scaleRate;

	this->Scale = { 1.0f, 1.0f, 1.0f };

	collision.position = position;
	collision.radius = Scale.x;
	count = 0;
}

void Explosion::Update()
{
	if (count >= interval) {
		count = 0;
		isExplobe = false;
	}
	else {
		Scale = Vector3::Lerp(Scale, maxScale, scaleRate);
		collision.position = position;
		collision.radius = Scale.x;
		ModelUpdate();
		count++;
	}
}

void Explosion::End()
{
}
