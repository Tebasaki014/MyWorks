#include "Actor.h"
#include"SDelete.h"

Actor3D::Actor3D(std::string modelPath)
{
	//モデルセット
	this->model = Model::CreateFromOBJ(modelPath);
	object = Object3D::Create(this->model);
	//ローカル軸初期化
	sideAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldX, qLocal));
	upAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldY, qLocal));
	forwordAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldZ, qLocal));
	//その他初期化処理
	this->Start();
}

Actor3D::Actor3D(Model* model)
{
	//モデルセット
	this->model = model;
	object = Object3D::Create(this->model);
	//ローカル軸初期化
	sideAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldX, qLocal));
	upAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldY, qLocal));
	forwordAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldZ, qLocal));
	//その他初期化処理
	this->Start();
}

Actor3D::Actor3D()
{
	//ローカル軸初期化
	sideAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldX, qLocal));
	upAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldY, qLocal));
	forwordAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldZ, qLocal));
	//その他初期化処理
	Start();
}

Actor3D::~Actor3D()
{
	//終了処理
	this->End();
	//ポインタ削除
	SDelete(model);
	SDelete(object);
}

void Actor3D::ModelUpdate()
{
	//ローカル軸更新
	sideAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldX, qLocal));
	upAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldY, qLocal));
	forwordAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldZ, qLocal));
	//座標、回転、スケール、ビルボードフラグをモデルに渡す
	object->SetPosition(this->position);
	object->SetScale(this->Scale);
	if (IsFixRotation) {
		object->SetRotation(qLocal);
	}
	//object->SetBillboard(billboordFlag);
	//モデル更新
	object->Update();
}

void Actor3D::Start()
{
}

void Actor3D::Update()
{
	this->ModelUpdate();
}

void Actor3D::End()
{
}

void Actor3D::Draw(const Shader& shader)
{
	object->Draw(shader);
}

void Actor3D::RotationVector(const Vector3& RollPitchYow)
{
	//回転クォータニオンを生成
	Quaternion qRoll = Quaternion::RotationAxis(upAxis, RollPitchYow.x);
	Quaternion qPitch = Quaternion::RotationAxis(sideAxis, RollPitchYow.y);
	Quaternion qYow = Quaternion::RotationAxis(forwordAxis, RollPitchYow.z);
	//回転クォータニオンを掛ける
	qLocal = qYow * qLocal;
	qLocal = qPitch * qLocal;
	qLocal = qRoll * qLocal;
}

void Actor3D::RotationQuaternion(const Quaternion& q)
{
	//回転クォータニオンを掛ける
	qLocal = q * qLocal;
}

Actor2D::Actor2D(Texture texIdx, const wchar_t* texturePath)
{
	Sprite::LoadTexture(texIdx, texturePath);
	sprite = Sprite::Create(texIdx, { 100.0f, 100.0f });
	sprite->SetSize({ 200.0f, 200.0f });
}

Actor2D::~Actor2D()
{
	SDelete(sprite);
}

void Actor2D::Update()
{
	sprite->SetPosition(this->position);
	sprite->SetRotation(this->rotation);
	sprite->SetSize(this->Size);
}

void Actor2D::Draw(DirectX::XMFLOAT4 color)
{
	sprite->Draw(color);
}
