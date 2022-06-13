#include "Actor.h"
#include"SDelete.h"

Actor3D::Actor3D(std::string modelPath)
{
	//���f���Z�b�g
	this->model = Model::CreateFromOBJ(modelPath);
	object = Object3D::Create(this->model);
	//���[�J����������
	sideAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldX, qLocal));
	upAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldY, qLocal));
	forwordAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldZ, qLocal));
	//���̑�����������
	this->Start();
}

Actor3D::Actor3D(Model* model)
{
	//���f���Z�b�g
	this->model = model;
	object = Object3D::Create(this->model);
	//���[�J����������
	sideAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldX, qLocal));
	upAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldY, qLocal));
	forwordAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldZ, qLocal));
	//���̑�����������
	this->Start();
}

Actor3D::Actor3D()
{
	//���[�J����������
	sideAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldX, qLocal));
	upAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldY, qLocal));
	forwordAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldZ, qLocal));
	//���̑�����������
	Start();
}

Actor3D::~Actor3D()
{
	//�I������
	this->End();
	//�|�C���^�폜
	SDelete(model);
	SDelete(object);
}

void Actor3D::ModelUpdate()
{
	//���[�J�����X�V
	sideAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldX, qLocal));
	upAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldY, qLocal));
	forwordAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldZ, qLocal));
	//���W�A��]�A�X�P�[���A�r���{�[�h�t���O�����f���ɓn��
	object->SetPosition(this->position);
	object->SetScale(this->Scale);
	if (IsFixRotation) {
		object->SetRotation(qLocal);
	}
	//object->SetBillboard(billboordFlag);
	//���f���X�V
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
	//��]�N�H�[�^�j�I���𐶐�
	Quaternion qRoll = Quaternion::RotationAxis(upAxis, RollPitchYow.x);
	Quaternion qPitch = Quaternion::RotationAxis(sideAxis, RollPitchYow.y);
	Quaternion qYow = Quaternion::RotationAxis(forwordAxis, RollPitchYow.z);
	//��]�N�H�[�^�j�I�����|����
	qLocal = qYow * qLocal;
	qLocal = qPitch * qLocal;
	qLocal = qRoll * qLocal;
}

void Actor3D::RotationQuaternion(const Quaternion& q)
{
	//��]�N�H�[�^�j�I�����|����
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
