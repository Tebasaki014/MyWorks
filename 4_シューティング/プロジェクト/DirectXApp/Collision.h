#pragma once
#include "Primitive.h"
class Collision
{
public:
	static bool CheckHit(const Sphere& sphere1, const Sphere& sphere2);
	static bool CheckHit(const Capsule& capsule1, const Capsule& capsule2);

	static bool CheckHit(const Sphere& sphere, const Box& box);
	static bool CheckHit(const Box& box, const Sphere& sphere) {
		return CheckHit(sphere, box);
	}

	static bool CheckHit(const Sphere& sphere, const Capsule& capsule);
	static bool CheckHit(const Capsule& capsule, const Sphere& sphere) {
		return CheckHit(sphere, capsule);
	}

	static bool CheckHit(const Sphere& sphere, const Ray& ray, Vector3* inter = nullptr, float* distance = nullptr);
	static bool CheckHit(const Ray& ray, const Sphere& sphere, Vector3* inter = nullptr, float* distance = nullptr) {
		return CheckHit(sphere, ray, inter, distance);
	}
};