#pragma once
#include<DirectXMath.h>

struct Vector2 : public DirectX::XMFLOAT2
{
	//float x, y;

	Vector2(float x, float y);
	Vector2();
	~Vector2();

	static Vector2 Zero();

	static float Length(Vector2 vector);
	static float LengthSquare(Vector2 vector);

	float Dot(Vector2 other) const;
	static float Dot(Vector2 vector1, Vector2 vector2);

	float Cross(Vector2 other) const;
	static float Cross(Vector2 vector1, Vector2 vector2);

	float Distance(Vector2 vector) const;
	static float Distance(Vector2 vectorA, Vector2 vectorB);

	Vector2& Nomalize();//���K��(������1��)����
	static  Vector2 Nomalize(Vector2 vector);//���K��static��

	bool IsZero() const;//0�Ȃ�true

	static float Clamp(float pos, float lowet, float heighest);

	static Vector2 Lerp(Vector2 startPosition, Vector2 endPosition, float timeRate);

	static Vector2 Blerp(Vector2 startPosition, Vector2 endPosition, Vector2 controlPoint, float timeRate);

	static Vector2 Blerp(Vector2 startPosition, Vector2 endPosition, Vector2 controlPoint, Vector2 controlPoint2, float timeRate);

	//���Z�q�I�[�o�[���[�h�̊F����(���Ԃ���v)
	//�� Vector2����ɂ���2��(float + Vector2�Ƃ�)�͏o���Ȃ��̂Œ���
	Vector2 operator +() const;
	Vector2 operator -() const;
	Vector2 operator +(const Vector2 vector) const;
	Vector2 operator +(const float scalor) const;
	Vector2 operator -(const Vector2 vector) const;
	Vector2 operator -(const float scalor) const;
	Vector2 operator *(const Vector2 vector) const;
	Vector2 operator *(const float scalor) const;
	Vector2 operator /(const Vector2 vector) const;
	Vector2 operator /(const float scalor) const;
	Vector2& operator +=(const Vector2 vector);
	Vector2& operator +=(const float scalor);
	Vector2& operator -=(const Vector2 vector);
	Vector2& operator -=(const float scalor);
	Vector2& operator *=(const Vector2 vector);
	Vector2& operator *=(const float scalor);
	Vector2& operator /=(const Vector2 vector);
	Vector2& operator /=(const float scalor);
};