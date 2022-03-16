#pragma once
#include"Vector3.h"
struct Quaternion: public DirectX::XMFLOAT4
{
	Quaternion(float x, float y, float z, float w);
	Quaternion();
	~Quaternion() = default;

	static Quaternion Identity() { return Quaternion(); }
	//”CˆÓ²ü‚è‰ñ“]
	static Quaternion RotationAxis(const Vector3& axis, float angle);
	static void RotationAxis(Quaternion& q, const Vector3& axis, float angle);
	//ƒxƒNƒgƒ‹‚ğp¨‚Å‰ñ“]
	static Quaternion RotationVector(const Vector3& v, const Quaternion& q);
	//ƒIƒCƒ‰[Šp‚Å‰ñ“]
	static Quaternion RotationEuler(const Vector3& RollPitchYow);
	//”CˆÓ‚Ì“_‚ğ’†S‚É”CˆÓ‚Ì²‚Å‰ñ“]
	static Vector3 RotationAround(const Vector3& rotatePosition, const Vector3& ankerPosition, const Vector3& axis, const float& angle);
	static Vector3 RotationAround(const Vector3& rotatePosition, const Vector3& ankerPosition, const float& distance, const Vector3& axis, const float& angle);
	//”CˆÓ‚Ì•ûŒü‚ğŒü‚­
	static Quaternion LookVector(const Vector3& direction, const Vector3& up = Vector3::WorldY());


	//“àÏ
	static float Dot(const Quaternion& q1, const Quaternion& q2);
	//ƒmƒ‹ƒ€
	static float Length(const Quaternion& q);
	//³‹K‰»
	static Quaternion Normalize(const Quaternion& q);
	Quaternion& Normalize();
	//‹¤–ğlŒ³”
	static Quaternion Conjugate(const Quaternion& q);

	//‰‰ZqƒI[ƒo[ƒ[ƒh‚ÌŠF—l
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

	//‹…–ÊüŒ`•âŠ®
	static Quaternion SLerp(const Quaternion& q1, const Quaternion& q2, float t);
	//üŒ`•âŠ®
	static Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t);
	//‰ñ“]s—ñ‚É•ÏŠ·
	static DirectX::XMMATRIX MatrixRotationQuaternion(const Quaternion& q);
	//‰ñ“]s—ñ‚©‚ç•ÏŠ·
	static Quaternion QuaternionRotationMatrix(const DirectX::XMMATRIX& m);
	//‰ñ“]²
	static Vector3 GetAxis(const Quaternion& q);
};