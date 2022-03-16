#pragma once
#include"Vector3.h"
struct Quaternion: public DirectX::XMFLOAT4
{
	Quaternion(float x, float y, float z, float w);
	Quaternion();
	~Quaternion() = default;

	static Quaternion Identity() { return Quaternion(); }
	//�C�ӎ������]
	static Quaternion RotationAxis(const Vector3& axis, float angle);
	static void RotationAxis(Quaternion& q, const Vector3& axis, float angle);
	//�x�N�g�����p���ŉ�]
	static Quaternion RotationVector(const Vector3& v, const Quaternion& q);
	//�I�C���[�p�ŉ�]
	static Quaternion RotationEuler(const Vector3& RollPitchYow);
	//�C�ӂ̓_�𒆐S�ɔC�ӂ̎��ŉ�]
	static Vector3 RotationAround(const Vector3& rotatePosition, const Vector3& ankerPosition, const Vector3& axis, const float& angle);
	static Vector3 RotationAround(const Vector3& rotatePosition, const Vector3& ankerPosition, const float& distance, const Vector3& axis, const float& angle);
	//�C�ӂ̕���������
	static Quaternion LookVector(const Vector3& direction, const Vector3& up = Vector3::WorldY());


	//����
	static float Dot(const Quaternion& q1, const Quaternion& q2);
	//�m����
	static float Length(const Quaternion& q);
	//���K��
	static Quaternion Normalize(const Quaternion& q);
	Quaternion& Normalize();
	//�����l����
	static Quaternion Conjugate(const Quaternion& q);

	//���Z�q�I�[�o�[���[�h�̊F�l
	Quaternion operator +() const;
	Quaternion operator -() const;
	Quaternion& operator +=(const Quaternion& q);
	Quaternion& operator -=(const Quaternion& q);
	Quaternion& operator *=(const float s);
	Quaternion& operator /=(const float s);
	Quaternion& operator *=(const Quaternion& q);
	Quaternion operator +(const Quaternion q) const;
	Quaternion operator -(const Quaternion q) const;
	Quaternion operator *(const Quaternion q) const;
	Quaternion operator *(float s) const;
	Quaternion operator /(float s) const;

	//���ʐ��`�⊮
	static Quaternion SLerp(const Quaternion& q1, const Quaternion& q2, float t);
	//���`�⊮
	static Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t);
	//��]�s��ɕϊ�
	static DirectX::XMMATRIX MatrixRotationQuaternion(const Quaternion& q);
	//��]�s�񂩂�ϊ�
	static Quaternion QuaternionRotationMatrix(const DirectX::XMMATRIX& m);
	//��]��
	static Vector3 GetAxis(const Quaternion& q);
};