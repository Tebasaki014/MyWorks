#include "Camera.h"
using namespace DirectX;

Camera::Camera(int window_width, int window_height)
{
	aspectRatio = (float)window_width / window_height;
	//�r���[�s��̌v�Z
	UpdateViewMatrix();
	// �ˉe�s��̌v�Z
	UpdateProjectionMatrix();
	// �r���[�v���W�F�N�V�����̍���
	matViewProjection = matView * matProjection;
}

void Camera::Update()
{
	if (viewDirty || projectionDirty) {
		// �Čv�Z�K�v�Ȃ�
		if (viewDirty) {
			// �r���[�s��X�V
			UpdateViewMatrix();
			viewDirty = false;
		}
		// �Čv�Z�K�v�Ȃ�
		if (projectionDirty) {
			// �r���[�s��X�V
			UpdateProjectionMatrix();
			projectionDirty = false;
		}
		// �r���[�v���W�F�N�V��������
		matViewProjection = matView * matProjection;
	}
}

void Camera::UpdateViewMatrix()
{
	//���_���W
	XMVECTOR eyePosition = XMLoadFloat3(&eye);
	//�����_���W
	XMVECTOR targetPosition = XMLoadFloat3(&target);
	//�i���́j�����
	XMVECTOR upVector = XMLoadFloat3(&up);
	//Z���i���������j
	XMVECTOR cameraAxisZ = XMVectorSubtract(targetPosition, eyePosition);
	//0�x�N�g�����ƌ�������܂�Ȃ��̂ŏ��O
	assert(!XMVector3Equal(cameraAxisZ, XMVectorZero()));
	assert(!XMVector3IsInfinite(cameraAxisZ));
	assert(!XMVector3Equal(upVector, XMVectorZero()));
	assert(!XMVector3IsInfinite(upVector));
	//���K��
	cameraAxisZ = XMVector3Normalize(cameraAxisZ);
	XMStoreFloat3(&lookAt, cameraAxisZ);

	//X���i�E�����j
	XMVECTOR cameraAxisX;
	//�������Z���̊O�ςŋ��܂�
	cameraAxisX = XMVector3Cross(upVector, cameraAxisZ);
	//���K��
	cameraAxisX = XMVector3Normalize(cameraAxisX);
	XMStoreFloat3(&right, cameraAxisX);

	//Y���i������j
	XMVECTOR cameraAxisY;
	//Z����X���̊O�ςŋ��܂�
	cameraAxisY = XMVector3Cross(cameraAxisZ, cameraAxisX);
	XMStoreFloat3(&up, cameraAxisY);

	// �J������]�s��
	XMMATRIX matCameraRot;
	// �J�������W�n�����[���h���W�n�̕ϊ��s��
	matCameraRot.r[0] = cameraAxisX;
	matCameraRot.r[1] = cameraAxisY;
	matCameraRot.r[2] = cameraAxisZ;
	matCameraRot.r[3] = XMVectorSet(0, 0, 0, 1);
	// �]�u�ɂ��t�s��i�t��]�j���v�Z
	matView = XMMatrixTranspose(matCameraRot);
	// ���_���W��-1���|�������W
	XMVECTOR reverseEyePosition = XMVectorNegate(eyePosition);
	// �J�����̈ʒu���烏�[���h���_�ւ̃x�N�g���i�J�������W�n�j
	XMVECTOR tX = XMVector3Dot(cameraAxisX, reverseEyePosition);	// X����
	XMVECTOR tY = XMVector3Dot(cameraAxisY, reverseEyePosition);	// Y����
	XMVECTOR tZ = XMVector3Dot(cameraAxisZ, reverseEyePosition);	// Z����
	// ��̃x�N�g���ɂ܂Ƃ߂�
	XMVECTOR translation = XMVectorSet(tX.m128_f32[0], tY.m128_f32[1], tZ.m128_f32[2], 1.0f);
	// �r���[�s��ɕ��s�ړ�������ݒ�
	matView.r[3] = translation;

#pragma region �S�����r���{�[�h�s��
	// �r���{�[�h�s��
	matBillboard.r[0] = cameraAxisX;
	matBillboard.r[1] = cameraAxisY;
	matBillboard.r[2] = cameraAxisZ;
	matBillboard.r[3] = XMVectorSet(0, 0, 0, 1);
#pragma region

#pragma region Y�����r���{�[�h�s��
	// �J����X���AY���AZ��
	XMVECTOR ybillCameraAxisX, ybillCameraAxisY, ybillCameraAxisZ;
	// X���͋���
	ybillCameraAxisX = cameraAxisX;
	// Y���̓��[���h���W�n��Y��
	ybillCameraAxisY = XMVector3Normalize(upVector);
	// Z����X����Y���̊O�ςŋ��܂�
	ybillCameraAxisZ = XMVector3Cross(ybillCameraAxisX, ybillCameraAxisY);
	// Y�����r���{�[�h�s��
	matBillboardY.r[0] = ybillCameraAxisX;
	matBillboardY.r[1] = ybillCameraAxisY;
	matBillboardY.r[2] = ybillCameraAxisZ;
	matBillboardY.r[3] = XMVectorSet(0, 0, 0, 1);
#pragma endregion
}

void Camera::UpdateProjectionMatrix()
{
	// �������e�ɂ��ˉe�s��̐���
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		aspectRatio,
		0.1f, 1000.0f
	);
}

void Camera::MoveEyeVector(const Vector3& move)
{
	// ���_���W���ړ����A���f
	Vector3 eye_moved = GetEye();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	SetEye(eye_moved);
}

void Camera::MoveVector(const Vector3& move)
{
	// ���_�ƒ����_���W�̈ړ��A���f
	Vector3 eye_moved = GetEye();
	Vector3 target_moved = GetTarget();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	target_moved.x += move.x;
	target_moved.y += move.y;
	target_moved.z += move.z;

	SetEye(eye_moved);
	SetTarget(target_moved);
}

void Camera::RotateAroundTarget(const Vector2& angle)
{
	Vector3 position = GetEye();
	Vector3 targetp = GetTarget();
	Vector3 upv = GetUp();
	position = position - targetp;
	
	Quaternion qCameraRightAngle = Quaternion::RotationAxis(upv, angle.x);
	Vector3 cameraSide = upv.Cross(-position).Nomalize();
	Quaternion qCameraUpAngle = Quaternion::RotationAxis(cameraSide, angle.y);

	Quaternion q = qCameraRightAngle * qCameraUpAngle;

	Quaternion qCameraPos = { position.x, position.y, position.z, 0.0f };
	Quaternion qq = Quaternion::Conjugate(q);
	qCameraPos = q * qCameraPos * qq;

	Quaternion qCameraUp = { upv.x, upv.y, upv.z, 0.0f };
	qCameraUp = q * qCameraUp * qq;

	position = { qCameraPos.x, qCameraPos.y, qCameraPos.z };
	upv = { qCameraUp.x, qCameraUp.y, qCameraUp.z };

	SetEye(position + targetp);
	SetUp(upv);
}

void Camera::RotateAround(const Vector3& ankerPoint, const Vector2& angle)
{
	Vector3 position = GetEye();
	Vector3 targetp = GetTarget();
	Vector3 upv = GetUp();
	Vector3 rightv = GetRight();
	position = Quaternion::RotationAround(position, target, upv, angle.x);
	//upv = Quaternion::RotationAround(upv, position, rightv );

	Vector3 lookv = Vector3::Nomalize(targetp - position);
	rightv = Vector3::Nomalize(Vector3::Cross(upv, lookv));

	position = Quaternion::RotationAround(position, target, rightv, angle.y);

	lookv = targetp - position;
	upv = Vector3::Cross(lookv, rightv);
	upv.Nomalize();
	rightv = Vector3::Cross(upv, lookv);
	rightv.Nomalize();
}

void Camera::Rota(Quaternion angle)
{
	Quaternion qq = Quaternion::Conjugate(angle);
	Vector3 pos = GetEye();
	Quaternion qPos = { pos.x, pos.y, pos.z, 0.0f };

	qPos = angle * qPos * qq;

	pos = { qPos.x, qPos.y, qPos.z };

	SetEye(pos);
}