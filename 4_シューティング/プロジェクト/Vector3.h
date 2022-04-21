#pragma once
#include<DirectXMath.h>

struct Vector3 : public DirectX::XMFLOAT3
{
	Vector3(float x, float y, float z);
	Vector3();
	~Vector3();

	static Vector3 Zero();
	static Vector3 WorldX();
	static Vector3 WorldY();
	static Vector3 WorldZ();

	static float Length(Vector3 vector);
	static float LengthSquare(Vector3 vector);

	float Dot(Vector3 other) const;
	static float Dot(Vector3 vector1, Vector3 vector2);

	Vector3 Cross(Vector3 other) const;
	static Vector3 Cross(Vector3 vector1, Vector3 Vector2);

	float Distance(Vector3 vector) const;
	static float Distance(Vector3 vector1, Vector3 vector2);
	float DistanceSquare(Vector3 vector) const;
	static float DistanceSquare(Vector3 vector1, Vector3 vector2);

	Vector3& Nomalize();//正規化(長さを1に)する
	static Vector3 Nomalize(Vector3 vector);//正規化static版

	bool IsZero() const;//0ならtrue

	static float Clamp(float pos, float lowest, float heighest);

	static Vector3 Lerp(Vector3 startPosition, Vector3 endPosition, float timeRate);

	static Vector3 Blerp(Vector3 startPosition, Vector3 endPosition, Vector3 controlPoint, float timeRate);

	static Vector3 Blerp(Vector3 startPosition, Vector3 endPosition, Vector3 controlPoint, Vector3 controlPoint2, float timeRate);

	//演算子オーバーロードの皆さん(たぶん大丈夫)
	//※ Vector3が後にくる2項(float + Vector3とか)は出来ないので注意
	Vector3 operator +() const;
	Vector3 operator -() const;
	Vector3 operator +(const Vector3 vector) const;
	Vector3 operator +(const float scalor) const;
	Vector3 operator -(const Vector3 vector) const;
	Vector3 operator -(const float scalor) const;
	Vector3 operator *(const Vector3 vector) const;
	Vector3 operator *(const float scalor) const;
	Vector3 operator /(const Vector3 vector) const;
	Vector3 operator /(const float scalor) const;
	Vector3& operator +=(const Vector3 vector);
	Vector3& operator +=(const float scalor);
	Vector3& operator -=(const Vector3 vector);
	Vector3& operator -=(const float scalor);
	Vector3& operator *=(const Vector3 vector);
	Vector3& operator *=(const float scalor);
	Vector3& operator /=(const Vector3 vector);
	Vector3& operator /=(const float scalor);
	bool operator ==(const Vector3 vector) const;
	bool operator !=(const Vector3 vector) const;
};