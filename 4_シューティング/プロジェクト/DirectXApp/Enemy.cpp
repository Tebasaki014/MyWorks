#include "Enemy.h"
#include <random>

int GetRandom(int min, int max) {
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> drc(min, max);

	return drc(mt);
}

void Move::Next(Move* newMove)
{
	enemy->SetNewMove(newMove);
}

#pragma region Enemy
void Enemy::Start()
{
	moveSpeed = 0.4f;
	dashSpeed = 3.5f;
	distancetop = D_State::OutRange;

	look = Quaternion::LookVector(player->position - position);
	SetRotation(Quaternion::SLerp(GetRotation(), look, 1.0f));

	distanceToPlayer = Vector3::Distance(position, player->position);

	bumodel = Model::CreateFromOBJ("gurumet");
	maru = Model::CreateFromOBJ("Ball");
	bullets.resize(10);
	for (auto& a : bullets) {
		a = new Bullet(bumodel);
	}
	homings.resize(6);
	for (auto& a : homings) {
		a = new Homing(bumodel);
	}
	explosion = new Explosion(maru);

	nowMove = new Blank(this);

	collision = new Sphere(position, 5.0f);
	ray = new Ray(position, forwordAxis);
	target = player->position;

	Vector3 c(1.0f, 0.2f, 0.1f);
	mslExp = new ParticleEmitter(15, position, 0.3f, 80, 2.0f, 0.1f, c, c);
}

void Enemy::Update()
{
	velocity = Vector3::Lerp(velocity, Vector3::Zero(), 0.1f);
	look = Quaternion::LookVector(player->position - position);
	distanceToPlayer = Vector3::Distance(position, player->position);
	std::vector<Bullet*> pbs = player->GetBullets();

	for (auto& a : pbs) {
		if (a->isShot) {
			if (Collision::CheckHit(*collision, *a->GetCollision())) {
				Damage(1);
				mslExp->Live(position);
			}
		}
	}
	
	nowMove->Update();

	position += velocity;
	ModelUpdate();
	bulletUpdate();
	collision->position = position;
	ray->position = position;
	ray->direction = forwordAxis;
	target = Vector3::Lerp(target, player->position, 0.06f);
}

void Enemy::Draw(const Shader& shader)
{
	if (!isDead) {
		object->Draw(shader);
	}
	for (auto& a : bullets) {
		if (a->isShot) {
			a->Draw(shader);
		}
	}
	for (auto& a : homings) {
		if (a->isShot) {
			a->Draw(shader);
		}
	}

	if (explosion->isExplobe) {
		explosion->Draw(shader);
	}
}

void Enemy::End()
{
	for (auto& a : bullets) {
		SDelete(a);
	}
	bullets.clear();
	for (auto& a : homings) {
		SDelete(a);
	}
	homings.clear();
	SDelete(collision);
	SDelete(nowMove);
	SDelete(ray);
	SDelete(explosion);
	SDelete(mslExp);
}

bool Enemy::Look()
{
	Sphere shoo(player->position, 5.0f);
	look = Quaternion::LookVector(player->position - position);
	SetRotation(Quaternion::SLerp(GetRotation(), look, 0.1f));

	if (Collision::CheckHit(shoo, *ray)) {
		return true;
	}
	else {
		return false;
	}
}

void Enemy::MeasureToPlayer()
{

	if (distanceToPlayer <= range) {

		if (distanceToPlayer <= farest) {
			distancetop = D_State::Far;

			if (distanceToPlayer <= nearest) {
				distancetop = D_State::Near;
			}
		}
		else {
			distancetop = D_State::AboutJust;
		}
	}
	else {
		distancetop = D_State::OutRange;
	}
}

void Enemy::shootBullet()
{
	for (auto& a : bullets) {
		if (!a->isShot) {
			a->isShot = true;
			a->Start(position, target, bulletspeed);
			break;
		}
	}
}

void Enemy::shootMissile()
{
	int i = 0;
	Vector3 pos = {};
	for (auto& a : homings) {
		if (!a->isShot) {
			a->isShot = true;
			
			pos = (position +(sideAxis * 4.0f)) + ((-forwordAxis * 2) + (-sideAxis * (i * 1.5f)));

			a->Start(pos, target, missilespeed);
			break;
		}
		i++;
	}
}

void Enemy::bulletUpdate()
{
	for (auto& a : bullets) {
		if (a->isShot) {
			a->Update();

			if (Collision::CheckHit(*a->GetCollision(), *player->GetCollision())) {
				player->Damage(1);
				mslExp->Live(position);
			}

			float dis = Vector3::Distance(position, a->position);
			if (dis >= range) {
				a->isShot = false;
			}
		}
	}

	for (auto& a : homings) {
		if (a->isShot) {
			if (a->state != Homing::State::Stay) {
				a->SetTarget(target);
			}

			a->Update();

			if (Collision::CheckHit(*a->GetCollision(), *player->GetCollision())) {
				player->Damage(1);
				mslExp->Live(player->position);
			}

			float dis = Vector3::Distance(position, a->position);
			if (dis >= distanceToPlayer) {
				a->isShot = false;
			}
		}
	}

	if (explosion->isExplobe) {
		explosion->Update();

		if (Collision::CheckHit(*explosion->GetCollision(), *player->GetCollision())) {
			player->Damage(5);
		}
	}
}

void Enemy::shootExplobe()
{
	if (!explosion->isExplobe) {
		explosion->isExplobe = true;
		explosion->Start(position, expScale, expRate);
	}
}

void Enemy::SetNewMove(Move* newMove)
{
	nowMove->End();
	nowMove = newMove;
	nowMove->Start();
}

void Enemy::Damage(int damage)
{
	HP -= damage;
	if (HP <= 0) {
		isDead = true;
	}
}

bool Enemy::InPlayerSite()
{
	if (Collision::CheckHit(*collision, *player->GetRay())) {
		return true;
	}
	else return false;
}
#pragma endregion

#pragma region Blank
void Blank::Update()
{
	count++;
	if (enemy->Look() && count >= 100) {
		Next(new Dash(enemy));
		//Next(new Missile(enemy));
	}
}
#pragma endregion

#pragma region Dash
void Dash::Start()
{
	direction = {};
	speed = 3.5f;
	repeat = GetRandom(1, 5);
	enemy->MeasureToPlayer();

	switch (enemy->distancetop)
	{
	case D_State::AboutJust:
		Next(new Attack(enemy));
		break;
	case D_State::Far:
		direction = enemy->GetForWordAxis();
		break;
	case D_State::Near:
		direction = -enemy->GetForWordAxis();
		break;
	case D_State::OutRange:
		direction = {};
		break;
	default:
		break;
	}

	if (enemy->InPlayerSite()) {
		int d = GetRandom(0, 1);

		if (d == 0) {
			direction = enemy->GetSideAxis();
		}
		else {
			direction = -enemy->GetSideAxis();
		}
	}

	direction.Nomalize();
}

void Dash::Update()
{
	if (count < repeat) {

		if (isStep) {

			if (Vector3::Length(enemy->velocity) <= 0.2f) {
				isStep = false;
				count++;
				Start();
			}
		}
		else {

			if (enemy->Look()) {
				enemy->velocity = direction * speed;
				isStep = true;
			}

		}
	}
	else {
		Next(new Attack(enemy));
	}
}
#pragma endregion

#pragma region Attack
void Attack::Update()
{
	if (enemy->Look()) {

		enemy->MeasureToPlayer();

		switch (enemy->distancetop)
		{
		case D_State::AboutJust:
			Next(new Shoot(enemy));
			break;
		case D_State::Far:
			Next(new Missile(enemy));
			break;
		case D_State::Near:
			Next(new Boom(enemy));
			break;
		case D_State::OutRange:
			Next(new Missile(enemy));
			break;
		default:
			break;
		}
	}

}
#pragma endregion

#pragma region Shoot
void Shoot::Update()
{
	if (repeat > shooted) {
		count++;

		if (count > interval) {
			count = 0;
			enemy->shootBullet();
			shooted++;
		}
	}
	else {
		Next(new Blank(enemy));
	}
}
#pragma endregion

#pragma region Missile
void Missile::Update()
{
	
	if (repeat > shooted) {

		if (count > 8) {
			enemy->shootMissile();
			count = 0;
			shooted++;
		}
		else {
			count++;
		}
	}
	else {
		Next(new Blank(enemy));
	}
}
#pragma endregion

#pragma region Boom
void Boom::Start()
{
	enemy->shootExplobe();
}
void Boom::Update()
{
	Next(new Dash(enemy));
}
void Boom::End()
{
}
#pragma endregion