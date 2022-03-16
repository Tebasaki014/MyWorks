#pragma once
#include"Model.h"
#include "Camera.h"
#include"Light.h"
#include"Shader.h"
#include"Quaternion.h"

//�O���錾(c4430�h�~)
class Shader;

class Object3D
{
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	// �p�C�v���C���Z�b�g
	struct PipelineSet
	{
		// ���[�g�V�O�l�`��
		ComPtr<ID3D12RootSignature> rootsignature;
		// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
		ComPtr<ID3D12PipelineState> pipelinestate;
	};

	// �萔�o�b�t�@�p�f�[�^�\����B0
	struct ConstBufferDataB0
	{
		XMMATRIX viewproj;	//�r���[�v���W�F�N�V�����s��
		XMMATRIX world;		//���[���h�s��
		Vector3 cameraPos;	//�J�������W
	};

private:
	// �f�o�C�X
	static ID3D12Device* dev;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;
	// �p�C�v���C��
	static PipelineSet pipelineSet;
	// �J����
	static Camera* camera;

	// �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuffB0; 
	// �F
	XMFLOAT4 color = { 1,1,1,1 };
	// ���[�J���X�P�[��
	Vector3 scale = { 1,1,1 };
	//��]�N�H�[�^�j�I��
	Quaternion rotation = Quaternion::Identity();

	// ���[�J�����W
	Vector3 position = { 0,0,0 };
	// ���[�J�����[���h�ϊ��s��
	XMMATRIX matWorld;
	// �e�I�u�W�F�N�g
	Object3D* parent = nullptr;
	// ���f��
	Model* model = nullptr;
	// �r���{�[�h
	bool isBillboard = false;

	//���[���h��(��]�p)�@�����̂����Ȃ�Ƃ�����
	const Vector3 worldX = { 1,0,0 };
	const Vector3 worldY = { 0,1,0 };
	const Vector3 worldZ = { 0,0,1 };
	//���[�J����(��]�p)
	Vector3 sideAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldX, rotation));
	Vector3 upAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldY, rotation));
	Vector3 forwordAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldZ, rotation));

public:
	//�ÓI������
	static void StaticInitialize(ID3D12Device* dev, Camera* camera = nullptr);
	//�`��O����
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);
	//�`��㏈��
	static void PostDraw();
	//3D�I�u�W�F�N�g����
	static Object3D* Create(Model* model = nullptr);
	//�J�����Z�b�g
	static void SetCamera(Camera* camera) {
		Object3D::camera = camera;
	}

	//������
	bool Initialize();
	//�X�V����
	void Update();
	//�`��
	void Draw(const Shader& shader);

	//���W�擾
	const Vector3& GetPosition() { return position; }
	//���W�ݒ�
	void SetPosition(Vector3 position) { this->position = position; }
	//��]�ݒ�
	void SetRotation(Quaternion rotation) { this->rotation = rotation; }
	//��]�N�H�[�^�j�I���擾
	const Quaternion& GetRotation() { return rotation; }
	//���[�J��X���擾
	const Vector3& GetSide() { return sideAxis; }
	//���[�J��Y���擾
	const Vector3& GetUp() { return upAxis; }
	//���[�J��Z���擾
	const Vector3& GetForword() { return forwordAxis; }
	//�x�N�g���ŉ�]
	void RotationVector(const Vector3& RollPitchYow);
	//�N�H�[�^�j�I���ŉ�]
	void RotationQuaternion(const Quaternion& q);
	
	//�X�P�[���ݒ�
	void SetScale(Vector3 scale) { this->scale = scale; }
	//���f���Z�b�g
	void SetModel(Model* model) { this->model = model; }
	//�r���{�[�h����H
	void SetBillboard(bool isBillboard) { this->isBillboard = isBillboard; }
	//Quaternion bill = Quaternion::Identity();
};