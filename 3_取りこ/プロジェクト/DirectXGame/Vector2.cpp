#include "Vector2.h"
#include<cmath>

//Vector2::Vector2(float x, float y)
//	:x(x),y(y)
//{}

Vector2::Vector2(float x, float y)
	: XMFLOAT2(x, y)
{}

Vector2::Vector2() 
	:x(0.0f),y(0.0f)
{}

Vector2::~Vector2() = default;

Vector2 Vector2::Zero() {
	return Vector2();//0ベクトル
}

float Vector2::Length(Vector2 vector) {
	return std::sqrt(vector.x * vector.x + vector.y * vector.y);//長さ
}

float Vector2::LengthSquare(Vector2 vector){
	return vector.x * vector.x + vector.y * vector.y;//長さの二乗
}

float Vector2::Dot(Vector2 other) const {
	return x * other.x + y * other.y;//内積
}

float Vector2::Dot(Vector2 vector1, Vector2 vector2) {
	return vector1.x * vector2.x + vector1.y * vector2.y;//内積
}

float Vector2::Cross(Vector2 other) const {
	return x * other.y - y * other.x;//外積
}

float Vector2::Cross(Vector2 vector1, Vector2 vector2) {
	return vector1.x * vector2.y - vector1.y * vector2.x;//外積
}

float Vector2::DistanceTo(Vector2 vector) const {
	return std::sqrt((vector.x - x) * (vector.x - x) + (vector.y - y) * (vector.y - y));//距離
}

float Vector2::DistanceAtoB(Vector2 vectorA, Vector2 vectorB) {
	return std::sqrt((vectorB.x - vectorA.x) * (vectorB.x - vectorA.x) + (vectorB.y - vectorA.y) * (vectorB.y - vectorA.y));//距離
}

Vector2& Vector2::Nomalize() {
	x = x / Length(*this);
	y = y / Length(*this);//正規化
	return *this;
}

Vector2 Vector2::Nomalize(Vector2 vector)
{
	return {vector.x / Length(vector), vector.y / Length(vector)};
}

bool Vector2::IsZero() const {
	return x == 0.0f && y == 0.0f;//ゼロかどうか
}

float Vector2::Clamp(float pos, float lowet, float heighest)
{
	if (pos <= lowet) {
		return lowet;
	}
	else if (pos >= heighest) {
		return heighest;
	}
	else{
		return pos;
	}
}

Vector2 Vector2::Lerp(Vector2 startPosition, Vector2 endPosition, float timeRate)
{
	return { startPosition.x + timeRate * (endPosition.x - startPosition.x), startPosition.y + timeRate * (endPosition.y - startPosition.y) };
}

Vector2 Vector2::Blerp(Vector2 startPosition, Vector2 endPosition, Vector2 controlPoint, float timeRate)
{
	return { ((1 - timeRate)*(1 - timeRate))*startPosition.x + 2 * (1 - timeRate)*timeRate*controlPoint.x + (timeRate * timeRate) * endPosition.x,
	((1 - timeRate)*(1 - timeRate))*startPosition.y + 2 * (1 - timeRate)*timeRate*controlPoint.y + (timeRate * timeRate) * endPosition.y };
}

Vector2 Vector2::Blerp(Vector2 startPosition, Vector2 endPosition, Vector2 controlPoint, Vector2 controlPoint2, float timeRate)
{
	return { ((1 - timeRate)*(1 - timeRate)*(1 - timeRate))*startPosition.x + 3 * ((1 - timeRate)*(1 - timeRate))*timeRate*controlPoint.x + 3 * (1 - timeRate)*(timeRate * timeRate) * controlPoint2.x + (timeRate * timeRate * timeRate) * endPosition.x,
	((1 - timeRate)*(1 - timeRate)*(1 - timeRate))*startPosition.y + 3 * ((1 - timeRate)*(1 - timeRate))*timeRate*controlPoint.y + 3 * (1 - timeRate)*(timeRate * timeRate) * controlPoint2.y + (timeRate * timeRate * timeRate) * endPosition.y };
}

Vector2 Vector2::operator+() const {
	return *this;
}

Vector2 Vector2::operator-() const{
	return{ -x, -y };
}

Vector2 Vector2::operator+(const Vector2 vector) const {
	return{ x + vector.x, y + vector.y };
}

Vector2 Vector2::operator+(const float scalor) const {
	return{ x + scalor,y + scalor };
}

Vector2 Vector2::operator-(const Vector2 vector) const {
	return{ x - vector.x, y - vector.y };
}

Vector2 Vector2::operator-(const float scalor) const {
	return{ x - scalor,y - scalor };
}

Vector2 Vector2::operator*(const Vector2 vector) const {
	return{ x * vector.x, y * vector.y };
}

Vector2 Vector2::operator*(const float scalor) const {
	return{ x * scalor,y * scalor };
}

Vector2 Vector2::operator/(const Vector2 vector) const {
	return{ x / vector.x, y / vector.y };
}

Vector2 Vector2::operator/(const float scalor) const {
	return{ x / scalor,y / scalor };
}

Vector2& Vector2::operator+=(const Vector2 vector) {
	x += vector.x;
	y += vector.y;
	return *this;
}

Vector2& Vector2::operator+=(const float scalor) {
	x += scalor;
	y += scalor;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2 vector) {
	x -= vector.x;
	y -= vector.y;
	return *this;
}

Vector2& Vector2::operator-=(const float scalor) {
	x -= scalor;
	y -= scalor;
	return *this;
}

Vector2& Vector2::operator*=(const Vector2 vector) {
	x *= vector.x;
	y *= vector.y;
	return *this;
}

Vector2& Vector2::operator*=(const float scalor) {
	x *= scalor;
	y *= scalor;
	return *this;
}

Vector2& Vector2::operator/=(const Vector2 vector) {
	x /= vector.x;
	y /= vector.y;
	return *this;
}

Vector2& Vector2::operator/=(const float scalor) {
	x /= scalor;
	y /= scalor;
	return *this;
}

//Vector2& Vector2::operator++() {
//	x += 1.0f;
//	y += 1.0f;
//	return *this;
//}
//
//Vector2& Vector2::operator--() {
//	x -= 1.0f;
//	y -= 1.0f;
//	return *this;
//}