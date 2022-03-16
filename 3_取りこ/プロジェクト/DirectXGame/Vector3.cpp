#include "Vector3.h"
#include<cmath>

//Vector3::Vector3(float x, float y, float z)
//	:x(x), y(y), z(z)
//{}

Vector3::Vector3(float x, float y, float z)
	: XMFLOAT3(x, y, z)
{}

Vector3::Vector3()
	: Vector3(0.0f, 0.0f, 0.0f)
{}

Vector3::~Vector3() = default;

Vector3 Vector3::Zero() {
	return Vector3();//0ベクトル
}

float Vector3::Length(Vector3 vector) {
	return std::sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);//長さ
}

float Vector3::LengthSquare(Vector3 vector) {
	return vector.x * vector.x + vector.y * vector.y + vector.z * vector.z;//長さの二乗
}

float Vector3::Dot(Vector3 other) const {
	return x * other.x + y * other.y + z * other.z;//内積
}

float Vector3::Dot(Vector3 vector1, Vector3 Vector3) {
	return vector1.x * Vector3.x + vector1.y * Vector3.y;//内積
}

Vector3 Vector3::Cross(Vector3 other) const {
	return{ y*other.z - z * other.y,z * other.x - x * other.z,x*other.y - y * other.x };//外積
}

Vector3 Vector3::Cross(Vector3 vector1, Vector3 vector2) {
	return{ vector1.y *vector2.z - vector1.z * vector2.y,vector1.z * vector2.x - vector1.x * vector2.z,vector1.x*vector2.y - vector1.y * vector2.x };//外積
}

float Vector3::DistanceTo(Vector3 vector) const {
	return std::sqrt((vector.x - x) * (vector.x - x) + (vector.y - y) * (vector.y - y) + (vector.z - z) * (vector.z - z));//距離
}

float Vector3::DistanceAtoB(Vector3 vectorA, Vector3 vectorB) {
	return std::sqrt((vectorB.x - vectorA.x) * (vectorB.x - vectorA.x) + (vectorB.y - vectorA.y) * (vectorB.y - vectorA.y) + (vectorB.y - vectorA.y) * (vectorB.z - vectorA.z));//距離
}

Vector3& Vector3::Nomalize() {
	x = x / Length(*this);
	y = y / Length(*this);
	z = z / Length(*this);//正規化
	return *this;
}

Vector3 Vector3::Nomalize(Vector3 vector)
{
	return { vector.x / Length(vector), vector.y / Length(vector), vector.z / Length(vector) };
}

bool Vector3::IsZero() const {
	return x == 0.0f && y == 0.0f && z == 0.0f;//ゼロかどうか
}

float Vector3::Clamp(float pos, float lowet, float heighest)
{
	if (pos <= lowet) {
		return lowet;
	}
	else if (pos >= heighest) {
		return heighest;
	}
	else {
		return pos;
	}
}

Vector3 Vector3::Lerp(Vector3 startPosition, Vector3 endPosition, float timeRate)
{
	return { startPosition.x + timeRate * (endPosition.x - startPosition.x), startPosition.y + timeRate * (endPosition.y - startPosition.y), startPosition.z + timeRate * (endPosition.z - startPosition.z) };
}

Vector3 Vector3::Blerp(Vector3 startPosition, Vector3 endPosition, Vector3 controlPoint, float timeRate)
{
	return { ((1 - timeRate)*(1 - timeRate))*startPosition.x + 2 * (1 - timeRate)*timeRate*controlPoint.x + (timeRate * timeRate) * endPosition.x,
	((1 - timeRate)*(1 - timeRate))*startPosition.y + 2 * (1 - timeRate)*timeRate*controlPoint.y + (timeRate * timeRate) * endPosition.y,
	((1 - timeRate)*(1 - timeRate))*startPosition.z + 2 * (1 - timeRate)*timeRate*controlPoint.z + (timeRate * timeRate) * endPosition.z };
}

Vector3 Vector3::Blerp(Vector3 startPosition, Vector3 endPosition, Vector3 controlPoint, Vector3 controlPoint2, float timeRate)
{
	return { ((1 - timeRate)*(1 - timeRate)*(1 - timeRate))*startPosition.x + 3 * ((1 - timeRate)*(1 - timeRate))*timeRate*controlPoint.x + 3 * (1 - timeRate)*(timeRate * timeRate) * controlPoint2.x + (timeRate * timeRate * timeRate) * endPosition.x,
	((1 - timeRate)*(1 - timeRate)*(1 - timeRate))*startPosition.y + 3 * ((1 - timeRate)*(1 - timeRate))*timeRate*controlPoint.y + 3 * (1 - timeRate)*(timeRate * timeRate) * controlPoint2.y + (timeRate * timeRate * timeRate) * endPosition.y,
	((1 - timeRate)*(1 - timeRate)*(1 - timeRate))*startPosition.z + 3 * ((1 - timeRate)*(1 - timeRate))*timeRate*controlPoint.z + 3 * (1 - timeRate)*(timeRate * timeRate) * controlPoint2.z + (timeRate * timeRate * timeRate) * endPosition.z };
}

Vector3 Vector3::operator+() const {
	return *this;
}

Vector3 Vector3::operator-() const {
	return{ -x, -y, -z };
}

Vector3 Vector3::operator+(const Vector3 vector) const {
	return{ x + vector.x, y + vector.y, z + vector.z };
}

Vector3 Vector3::operator+(const float scalor) const {
	return{ x + scalor,y + scalor, z + scalor };
}

Vector3 Vector3::operator-(const Vector3 vector) const {
	return{ x - vector.x, y - vector.y, z - vector.z };
}

Vector3 Vector3::operator-(const float scalor) const {
	return{ x - scalor,y - scalor, z - scalor};
}

Vector3 Vector3::operator*(const Vector3 vector) const {
	return{ x * vector.x, y * vector.y, z * vector.z };
}

Vector3 Vector3::operator*(const float scalor) const {
	return{ x * scalor,y * scalor, z * scalor };
}

Vector3 Vector3::operator/(const Vector3 vector) const {
	return{ x / vector.x, y / vector.y, z / vector.z };
}

Vector3 Vector3::operator/(const float scalor) const {
	return{ x / scalor,y / scalor, z / scalor };
}

Vector3& Vector3::operator+=(const Vector3 vector) {
	x += vector.x;
	y += vector.y;
	z += vector.z;
	return *this;
}

Vector3& Vector3::operator+=(const float scalor) {
	x += scalor;
	y += scalor;
	z += scalor;
	return *this;
}

Vector3& Vector3::operator-=(const Vector3 vector) {
	x -= vector.x;
	y -= vector.y;
	z -= vector.z;
	return *this;
}

Vector3& Vector3::operator-=(const float scalor) {
	x -= scalor;
	y -= scalor;
	z -= scalor;
	return *this;
}

Vector3& Vector3::operator*=(const Vector3 vector) {
	x *= vector.x;
	y *= vector.y;
	z *= vector.z;
	return *this;
}

Vector3& Vector3::operator*=(const float scalor) {
	x *= scalor;
	y *= scalor;
	z *= scalor;
	return *this;
}

Vector3& Vector3::operator/=(const Vector3 vector) {
	x /= vector.x;
	y /= vector.y;
	z /= vector.z;
	return *this;
}

Vector3& Vector3::operator/=(const float scalor) {
	x /= scalor;
	y /= scalor;
	z /= scalor;
	return *this;
}

Vector3 Vector3::operator=(const XMFLOAT3 xmfloat3) const
{
	return { xmfloat3.x, xmfloat3.y, xmfloat3.z };
}
