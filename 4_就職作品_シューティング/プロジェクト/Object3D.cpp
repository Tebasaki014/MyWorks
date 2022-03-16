#include "Object3D.h"
#include <d3dcompiler.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;

ID3D12Device* Object3D::dev = nullptr;
ID3D12GraphicsCommandList* Object3D::cmdList = nullptr;
Object3D::PipelineSet Object3D::pipelineSet;
Camera* Object3D::camera = nullptr;

void Object3D::StaticInitialize(ID3D12Device* dev, Camera* camera)
{
	//�ď������`�F�b�N
	assert(!Object3D::dev);

	//nullptr�`�F�b�N
	assert(dev);

	Object3D::dev = dev;
	Object3D::camera = camera;

	//���f���̐ÓI������
	Model::StaticInitialize(dev);
}

void Object3D::PreDraw(ID3D12GraphicsCommandList* cmdList)
{
	//PreDraw��PostDraw���y�A�ŌĂ΂�Ă��Ȃ���΃G���[
	assert(Object3D::cmdList == nullptr);
	//�R�}���h���X�g���Z�b�g
	Object3D::cmdList = cmdList;
	//�v���~�e�B�u�`���ݒ�
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Object3D::PostDraw()
{
	//�R�}���h���X�g����
	Object3D::cmdList = nullptr;
}

Object3D* Object3D::Create(Model* model)
{
	//3D�I�u�W�F�N�g�̃C���X�^���X�𐶐�
	Object3D* object3D = new Object3D();
	if (object3D == nullptr) {
		return nullptr;
	}

	//������
	if (!object3D->Initialize()) {
		delete object3D;
		assert(0);
	}

	if (model) {
		object3D->SetModel(model);
	}

	return object3D;
}

bool Object3D::Initialize()
{
	//nullptr�`�F�b�N
	assert(dev);
	HRESULT result;
	//�萔�o�b�t�@
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), 	//�A�b�v���[�h��
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB0) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB0));

	return true;
}

void Object3D::Update()
{
	assert(camera);

	HRESULT result;
	XMMATRIX matScale, matRot,matTrans;

	if (isBillboard) {
		const Quaternion bill = Quaternion::QuaternionRotationMatrix(camera->GetBillboardMatrix());
		rotation = rotation * bill;
	}

	// �X�P�[���A��]�A���s�ړ��s��̌v�Z
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	matRot = XMMatrixIdentity();
	matRot = Quaternion::MatrixRotationQuaternion(rotation);
	matTrans = XMMatrixTranslation(position.x, position.y, position.z);
	// ���[���h�s��̍���
	matWorld = XMMatrixIdentity(); //���Z�b�g
	matWorld *= matScale; //�X�P�[��
	matWorld *= matRot; //��]
	matWorld *= matTrans; //���s�ړ�


	//�e�I�u�W�F�N�g�������
	if (parent != nullptr) {
		//�e�I�u�W�F�N�g�̃��[���h�s����|����
		matWorld *= parent->matWorld;
	}

	const XMMATRIX& matViewProjection = camera->GetViewProjectionMatrix();

	// �萔�o�b�t�@�փf�[�^�]��
	ConstBufferDataB0* constMap = nullptr;
	result = constBuffB0->Map(0, nullptr, (void**)&constMap);
	constMap->viewproj = matViewProjection;	//�r���[�s��
	constMap->world = matWorld;				//���[���h�s��
	constMap->cameraPos = camera->GetEye();	//�J�������W
	constBuffB0->Unmap(0, nullptr);

	camera->Update();

	//���[�J��������]
	sideAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldX, rotation));
	upAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldY, rotation));
	forwordAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldZ, rotation));
}

void Object3D::Draw(const Shader& shader)
{
	//nullptr�`�F�b�N
	assert(dev);
	assert(Object3D::cmdList);

	//���f���̊��蓖�Ă��Ȃ���Ε`�悵�Ȃ�
	if (model == nullptr) {
		return;
	}

	//�p�C�v���C���X�e�[�g
	//cmdList->SetPipelineState(pipelineSet.pipelinestate.Get());
	cmdList->SetPipelineState(shader.pipelinestate.Get());
	//���[�g�V�O�l�`��
	cmdList->SetGraphicsRootSignature(shader.rootsignature.Get());
	//�萔�o�b�t�@�r���[
	cmdList->SetGraphicsRootConstantBufferView(0, constBuffB0->GetGPUVirtualAddress());

	//���C�g�̕`��R�}���h
	Light::GetInstance()->Draw(cmdList, 3);
	//�`��
	model->Draw(cmdList);
}

void Object3D::RotationVector(const Vector3& RollPitchYow)
{
	Quaternion qRoll = Quaternion::RotationAxis(upAxis, RollPitchYow.x);
	Quaternion qPitch = Quaternion::RotationAxis(sideAxis, RollPitchYow.y);
	Quaternion qYow = Quaternion::RotationAxis(forwordAxis, RollPitchYow.z);

	rotation = qRoll * rotation;
	rotation = qPitch * rotation;
	rotation = qYow * rotation;
}

void Object3D::RotationQuaternion(const Quaternion& q)
{
	rotation = q * rotation;
}