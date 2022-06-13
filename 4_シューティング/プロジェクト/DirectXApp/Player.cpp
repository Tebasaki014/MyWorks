#include "Player.h"

float Clamp(const float& num, const float& min, const float& max) {
	if (num <= min || num >= max) {
		if (num <= min) {
			return min;
		}
		if (num >= max) {
			return max;
		}
		else return num;
	}
	else return num;
}

float Rann(const float& min, const float& max) {
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_real_distribution<float> drc(min, max);

	return drc(mt);
}

void Player::Start()
{
	cameraOffset = { 2.0f, 3.0f, 0 };
	cameraSpeed = { 0.003f, 0.003f, 0.0f };
	cameraDistance = 8.0f;
	targetDistance = 20.0f; 
	moveAccel = 0.4f;
	stepAccel = 5.0f;

	cameraTarget = forwordAxis * targetDistance;
	cameraPos = -forwordAxis * cameraDistance;
	cameraPos += sideAxis * cameraOffset.x;
	cameraPos += upAxis * cameraOffset.y;
	cameraPos += position;

	cam->SetEye(cameraPos);
	cam->SetTarget(cameraTarget);

	IsFixRotation = false;
	object->SetRotation(qLocal);

	bbm = Model::CreateFromOBJ("gurumet");

	bullets.resize(10);
	for (auto& a : bullets) {
		a = new Bullet(bbm);
	}

	ray = new Ray(position, forwordAxis);
	collision = new Sphere(position, 1.0f);

	Vector3 c(0.1f, 0.1f, 1.0f);
	boost = new ParticleEmitter(5, position, 0.5f, 20, 1.0f, 2.0f, c, c);
	walk = new ParticleEmitter(20, position, 0.07f, 1, 0.3f, 0.1f, c, c);

	vivrateFrame = 5;
	vivrateRange = 0.2f;
}

void Player::Update()
{
	playerVelocity = Vector3::Lerp(playerVelocity, Vector3::Zero(), 0.1f);

	if (isStep) {

		if (Vector3::Length(playerVelocity) <= 0.2f) {
			isStep = false;
		}
	}
	else {
		if (input->IsKeyTouch(DIK_A)) {
			playerVelocity = -sideAxis;
		}
		else if (input->IsKeyTouch(DIK_D)) {
			playerVelocity = sideAxis;
		}
		else if (input->IsKeyTouch(DIK_S)) {
			playerVelocity = -forwordAxis;
		}
		else if (input->IsKeyTouch(DIK_W)) {
			playerVelocity = forwordAxis;
		}

		if (input->IsKeyDown(DIK_SPACE)) {
			if (Vector3::Length(playerVelocity) <= 0.2f) {
				playerVelocity = -forwordAxis * 3.0f;
			}
			else {
				playerVelocity *= stepAccel;
			}

			isStep = true;
		}
		else {
			playerVelocity *= moveAccel;
		}
	}

	if (!input->IsKeyTouch(DIK_O)) {
		cameraAngle += input->GetMouseMove() * cameraSpeed;
	}

	cameraAngle.y = Clamp(cameraAngle.y, -0.8f, 0.8f);

	qLocal = Quaternion::RotationEuler(Vector3(cameraAngle.x, cameraAngle.y, 0.0f));

	cameraTarget = forwordAxis * targetDistance;
	cameraPos = -forwordAxis * cameraDistance;
	cameraPos += sideAxis * cameraOffset.x;
	cameraPos += upAxis * cameraOffset.y;
	cameraPos += position;
	cameraTarget += position;

	if (input->IsMousekeyDown(0)) {
		shootBullet();
	}

	if (input->IsKeyDown(DIK_G)) {
		isVible = true;
	}

	if (playerVelocity != Vector3::Zero()) {
		Vector3 ax = Vector3::Cross(upAxis, playerVelocity * 0.55f);
		Quaternion look = Quaternion::RotationAxis(ax, 0.6f) * qLocal;
		object->SetRotation(Quaternion::SLerp(object->GetRotation(), look, 0.08f));
		playerVelocity.y = 0.0f;
		position += playerVelocity;
	}

	cam->SetUp(upAxis);

	if (isVible) {
		cam->SetEye(CameraVivlate(vivrateRange));
	}
	else {
		cam->SetEye(cameraPos);
	}
	
	cam->SetTarget(cameraTarget);

	ray->position = position;
	ray->direction = forwordAxis;
	collision->position = position;

	bulletUpdate();
	ModelUpdate();

	if (isStep && Vector3::Length(playerVelocity) >= 2.0f) {
		boost->SetGravity(Vector3(0.0f, -0.06f, 0.0f));
		boost->Live(position);
	}
	else if(Vector3::Length(playerVelocity) >= 0.1f) {
		walk->SetGravity(upAxis * 0.01f);
		walk->Live(position + -upAxis * 2.0f);
	}
}

void Player::End()
{
	for (auto& a : bullets) {
		SDelete(a);
	}
	bullets.clear();
	SDelete(ray);
	SDelete(collision);
	SDelete(boost);
}

void Player::Draw(const Shader& shader)
{
	object->Draw(shader);
	for (auto& a : bullets) {
		if (a->isShot) {
			a->Draw(shader);
		}
	}
}

void Player::shootBullet()
{
	for (auto& a : bullets) {
		if (!a->isShot) {
			a->isShot = true;
			a->Start(position, cameraTarget, bulletspeed);
			break;
		}
	}
}

void Player::bulletUpdate()
{
	for (auto& a : bullets) {
		if (a->isShot) {
			a->Update();

			if (Vector3::Distance(position, a->position) >= range) {
				a->isShot = false;
			}
		}
	}
}

Vector3 Player::CameraVivlate(float range)
{
	Vector3 vivle = {};
	
	count++;
	vivle.x = Rann(-1.0f, 1.0f);
	vivle.y = Rann(-1.0f, 1.0f);
	vivle.z = Rann(-1.0f, 1.0f);

	if (count >= vivrateFrame) {
		isVible = false;
		count = 0;
	}

	return (Vector3::Nomalize(vivle) * range) + cameraPos;
}

void Player::Damage(int damage)
{
	HP -= damage;
	if (HP <= 0) {
		isDead = true;
	}

	isVible = true;
}

PostEffectModoki::PostEffectModoki()
{
}
