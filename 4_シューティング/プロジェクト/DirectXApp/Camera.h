#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"

class Camera
{
protected:
	// DirectX::���ȗ�
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

	//�r���[�s��
	XMMATRIX matView = DirectX::XMMatrixIdentity();
	//�r���{�[�h�s��
	XMMATRIX matBillboard = DirectX::XMMatrixIdentity();
	//Y�����r���{�[�h�s��
	XMMATRIX matBillboardY = DirectX::XMMatrixIdentity();
	//�ˉe�s��
	XMMATRIX matProjection = DirectX::XMMatrixIdentity();
	//�r���[�ˉe�s��
	XMMATRIX matViewProjection = DirectX::XMMatrixIdentity();
	//�r���[�s��_�[�e�B�t���O
	bool viewDirty = false;
	//�ˉe�s��_�[�e�B�t���O
	bool projectionDirty = false;
	//���_���W
	Vector3 eye = { 0, 0, -20 };
	//�����_���W
	Vector3 target = { 0, 0, 0 };
	//�����
	Vector3 up = { 0, 1, 0 };
	//�E����
	Vector3 right = { 1, 0, 0 };
	//��������
	Vector3 lookAt = { 0, 0, 1 };
	//���[���h���WY
	const Vector3 worldY = { 0, 1, 0 };
	//�A�X�y�N�g��
	float aspectRatio = 1.0f;

public:

	Camera(int window_width, int window_height);
	virtual ~Camera() = default;

	//�X�V
	virtual void Update();
	//�r���[�s��X�V
	void UpdateViewMatrix();
	//�ˉe�s��X�V
	void UpdateProjectionMatrix();
	//�r���[�s��擾
	inline const XMMATRIX& GetViewMatrix() {
		return matView;
	}
	//�ˉe�s��擾
	inline const XMMATRIX& GetProjectionMatrix() {
		return matProjection;
	}
	//�r���[�ˉe�s��擾
	inline const XMMATRIX& GetViewProjectionMatrix() {
		return matViewProjection;
	}
	//�r���{�[�h�s��擾
	inline const XMMATRIX& GetBillboardMatrix() {
		return matBillboard;
	}
	//�����_���W�擾
	inline const Vector3& GetEye() {
		return eye;
	}
	//���_���W�ݒ�
	inline void SetEye(Vector3 eye) {
		this->eye = eye; viewDirty = true;
	}
	//�����_���W�擾
	inline const Vector3& GetTarget() {
		return target;
	}
	//�����_���W�ݒ�
	inline void SetTarget(Vector3 target) {
		this->target = target; viewDirty = true;
	}
	//������擾
	inline const Vector3& GetUp() {
		return up;
	}
	//�E�����擾
	inline const Vector3& GetRight() {
		return right;
	}
	//���������擾
	inline const Vector3& GetLook() {
		return lookAt;
	}
	//�����
	inline void SetUp(Vector3 up) {
		this->up = up; viewDirty = true;
	}
	//�E����
	inline void SetRight(Vector3 right) {
		this->right = right; viewDirty = true;
	}
	//�����_���ƈړ�
	void MoveEyeVector(const Vector3 & move);
	//�{�̂����ړ�
	void MoveVector(const Vector3 & move);
	//�����_�𒆐S�ɉ�]
	void RotateAroundTarget(const Vector2& angle);
	//����_�𒆐S�ɉ�]
	void RotateAround(const Vector3& ankerPoint, const Vector2& angle);

	void Rota(Quaternion angle);
};