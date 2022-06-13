#include "Quaternion.h"
#include <cmath>

Quaternion::Quaternion(float x, float y, float z, float w) 
	:DirectX::XMFLOAT4{ x,y,z,w }
{}

Quaternion::Quaternion()
	: DirectX::XMFLOAT4{ 0.0f, 0.0f, 0.0f , 1.0f }
{}

Quaternion Quaternion::RotationAxis(const Vector3& axis, float angle)
{
	float _sin = sin(angle / 2.0f);
	return { _sin * axis.x, _sin * axis.y, _sin * axis.z, cos(angle / 2.0f) };
}

void Quaternion::RotationAxis(Quaternion& q, const Vector3& axis, float angle)
{
	float _sin = sin(angle / 2.0f);
	q = { _sin * axis.x, _sin * axis.y, _sin * axis.z, cos(angle / 2.0f) };
}

Quaternion Quaternion::RotationVector(const Vector3& v, const Quaternion& q)
{
	Quaternion qq = Conjugate(q);

	Quaternion qv = { v.x, v.y, v.z, 0 };
	Quaternion result = q * qv * qq;

	return result;
}

Quaternion Quaternion::RotationEuler(const Vector3& RollPitchYow)
{
	Quaternion result = Quaternion::Identity();
	Quaternion roll = Quaternion::RotationAxis(Vector3::WorldY(), RollPitchYow.x);
	Quaternion pitch = Quaternion::RotationAxis(Vector3::WorldX(), RollPitchYow.y);
	Quaternion yow = Quaternion::RotationAxis(Vector3::WorldZ(), RollPitchYow.z);

	result = yow * result;
	result = pitch * result;
	result = roll * result;

	return result;
}

Vector3 Quaternion::RotationAround(const Vector3& rotatePosition, const Vector3& ankerPosition, const Vector3& axis, const float& angle)
{
	Quaternion q = RotationAxis(axis, angle);
	Quaternion qq = Conjugate(q);

	Vector3 pos = rotatePosition - ankerPosition;
	Quaternion qv = { pos.x, pos.y, pos.z, 0.0f };
	Quaternion qa = q * qv * qq;

	Vector3 result = { qa.x, qa.y, qa.z };

	return result + ankerPosition;
}

Vector3 Quaternion::RotationAround(const Vector3& rotatePosition, const Vector3& ankerPosition, const float& distance, const Vector3& axis, const float& angle)
{
	Quaternion q = RotationAxis(axis, angle);
	Quaternion qq = Conjugate(q);
	
	Vector3 pos = Vector3::Nomalize(rotatePosition - ankerPosition) *=distance;
	Quaternion qv = { pos.x, pos.y, pos.z, 0.0f };
	Quaternion qa = q * qv * qq;
	qa.Normalize() *= distance;

	Vector3 result = { qa.x, qa.y, qa.z };

	return result + ankerPosition;
}

Quaternion Quaternion::LookVector(const Vector3& direction, const Vector3& up)
{
	Vector3 z = Vector3::Nomalize(direction);
	Vector3 x = Vector3::Cross(up, z);
	Vector3 y = Vector3::Cross(z, x);

	DirectX::XMMATRIX m = DirectX::XMMatrixSet(
		x.x, x.y, x.z, 0.0f,
		y.x, y.y, y.z, 0.0f,
		z.x, z.y, z.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

	Quaternion result = Quaternion::QuaternionRotationMatrix(m);

	return result;
}

float Quaternion::Dot(const Quaternion& q1, const Quaternion& q2)
{
	float result;
	result = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
	return result;
}

float Quaternion::Length(const Quaternion& q)
{
	float w;
	float x;
	float y;
	float z;
	float result;
	w = q.w * q.w;
	x = q.x * q.x;
	y = q.y * q.y;
	z = q.z * q.z;
	result = sqrt(w + x + y + z);

	return result;
}

Quaternion Quaternion::Normalize(const Quaternion& q)
{
	Quaternion result = q;
	float len = Length(result);
	if (len != 0)
	{
		result /= len;

	}
	return result;
}

Quaternion& Quaternion::Normalize()
{
	float len = Length(*this);
	if (len != 0)
	{
		*this /= len;
	}
	return *this;
}

Quaternion Quaternion::Conjugate(const Quaternion& q)
{
	Quaternion result = { -q.x,-q.y,-q.z,q.w, };
	return result;
}

Quaternion Quaternion::operator+() const
{
	return *this;
}

Quaternion Quaternion::operator-() const
{
	return { -x,-y,-z,-w, };
}

Quaternion& Quaternion::operator+=(const Quaternion& q)
{
	x += q.x;
	y += q.y;
	z += q.z;
	w += q.w;
	return *this;
}

Quaternion& Quaternion::operator-=(const Quaternion& q)
{
	x -= q.x;
	y -= q.y;
	z -= q.z;
	w -= q.w;
	return *this;
}

Quaternion& Quaternion::operator*=(const float s)
{
	x *= s;
	y *= s;
	z *= s;
	w *= s;
	return *this;
}

Quaternion& Quaternion::operator/=(const float s)
{
	x *= 1.0f / s;
	y *= 1.0f / s;
	z *= 1.0f / s;
	w *= 1.0f / s;
	return *this;
}

Quaternion& Quaternion::operator*=(const Quaternion& q)
{
	Quaternion result = Quaternion::Identity();
	result = {
		x * q.w + y * q.z - z * q.y + w * q.x,
		-x * q.z + y * q.w + z * q.x + w * q.y,
		x * q.y - y * q.x + z * q.w + w * q.z,
		-x * q.x - y * q.y - z * q.z + w * q.w
	};

	*this = result;
	return *this;
}

Quaternion Quaternion::operator+(const Quaternion q) const
{
	return { x + q.x, y + q.y, z + q.z, w + q.w };
}

Quaternion Quaternion::operator-(const Quaternion q) const
{
	return { x - q.x, y - q.y, z - q.z, w - q.w };
}

Quaternion Quaternion::operator*(const Quaternion q) const
{
	Quaternion result = *this;
	return result *= q;
}

Quaternion Quaternion::operator*(float s) const
{
	Quaternion result = *this;
	return  result *= s;
}

Quaternion Quaternion::operator/(float s) const
{
	Quaternion result = *this;
	return result /= s;
}

Quaternion Quaternion::SLerp(const Quaternion& q1, const Quaternion& q2, float t)
{
	float cos = Dot(q1, q2);
	Quaternion t2 = q2;
	if (cos < 0.0f){
		cos = -cos;
		t2 = -q2;
	}
	float k0 = 1.0f - t;
	float k1 = t;
	if ((1.0f - cos) > 0.001f){
		float theta = (float)acos(cos);
		k0 = (float)(sin(theta * k0) / sin(theta));
		k1 = (float)(sin(theta * k1) / sin(theta));

	}
	return q1 * k0 + t2 * k1;
}

Quaternion Quaternion::Lerp(const Quaternion& q1, const Quaternion& q2, float t)
{
	float cos = Dot(q1, q2);
	Quaternion t2 = q2;
	if (cos < 0.0f)
	{
		cos = -cos;
		t2 = -q2;
	}
	float  k0 = 1.0f - t;
	float k1 = t;
	return q1 * k0 + t2 * k1;
}

DirectX::XMMATRIX Quaternion::MatrixRotationQuaternion(const Quaternion& q)
{
	float xx = q.x * q.x * 2.0f;
	float yy = q.y * q.y * 2.0f;
	float zz = q.z * q.z * 2.0f;
	float xy = q.x * q.y * 2.0f;
	float xz = q.x * q.z * 2.0f;
	float yz = q.y * q.z * 2.0f;
	float wx = q.w * q.x * 2.0f;
	float wy = q.w * q.y * 2.0f;
	float wz = q.w * q.z * 2.0f;

	DirectX::XMMATRIX result = DirectX::XMMatrixSet(
		1.0f - yy - zz, xy + wz         , xz - wy       , 0.0f, 
		xy - wz       , 1.0f - xx - zz  , yz + wx       , 0.0f, 
		xz + wy       , yz - wx         , 1.0f - xx - yy, 0.0f, 
		0.0f          , 0.0f            , 0.0f          , 1.0f 
	);

	return result;
}

Quaternion Quaternion::QuaternionRotationMatrix(const DirectX::XMMATRIX& m)
{
	Quaternion result;
	DirectX::XMVECTOR vec = DirectX::XMQuaternionRotationMatrix(m);
	DirectX::XMStoreFloat4(&result ,vec);
	return result;
}

Vector3 Quaternion::GetAxis(const Quaternion& q)
{
	Vector3 result;
	float x = q.x;
	float y = q.y;
	float z = q.z;
	float _len = Length(q);
	result.x = x / _len;
	result.y = y / _len;
	result.z = z / _len;
	return result;
}