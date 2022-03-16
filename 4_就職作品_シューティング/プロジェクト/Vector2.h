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

	Vector2& Nomalize();//正規化(長さを1に)する
	static  Vector2 Nomalize(Vector2 vector);//正規化static版

	bool IsZero() const;//0ならtrue

	static float Clamp(float pos, float lowet, float heighest);

	static Vector2 Lerp(Vector2 startPosition, Vector2 endPosition, float timeRate);

	static Vector2 Blerp(Vector2 startPosition, Vector2 endPosition, Vector2 controlPoint, float timeRate);

	static Vector2 Blerp(Vector2 startPosition, Vector2 endPosition, Vector2 controlPoint, Vector2 controlPoint2, float timeRate);

	//演算子オーバーロードの皆さん(たぶん大丈夫)
	//※ Vector2が後にくる2項(float + Vector2とか)は出来ないので注意
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