#include "Collision.h"

bool Collision::CheckHit(const Sphere & sphere1, const Sphere & sphere2)
{
	if (Vector3::Distance(sphere1.position, sphere2.position) <= sphere1.radius + sphere2.radius) {
		return true;
	}
	else return false;
}

bool Collision::CheckHit(const Capsule& capsule1, const Capsule& capsule2)
{

	return false;
}

bool Collision::CheckHit(const Sphere & sphere, const Box & box)
{
	float distansq = 0.0f;

	if (sphere.position.x < box.minPosition.x) {
		distansq += (sphere.position.x - box.minPosition.x) * (sphere.position.x - box.minPosition.x);
	}
	if (sphere.position.x > box.maxPosition.x) {
		distansq += (sphere.position.x - box.maxPosition.x) * (sphere.position.x - box.maxPosition.x);
	}

	if (sphere.position.y < box.minPosition.y) {
		distansq += (sphere.position.y - box.minPosition.y) * (sphere.position.y - box.minPosition.y);
	}
	if (sphere.position.y > box.maxPosition.y) {
		distansq += (sphere.position.y - box.maxPosition.y) * (sphere.position.y - box.maxPosition.y);
	}

	if (sphere.position.z < box.minPosition.z) {
		distansq += (sphere.position.z - box.minPosition.z) * (sphere.position.z - box.minPosition.z);
	}
	if (sphere.position.z > box.maxPosition.z) {
		distansq += (sphere.position.z - box.maxPosition.z) * (sphere.position.z - box.maxPosition.z);
	}

	if (distansq < +(sphere.radius * sphere.radius)) {
		return true;
	}
	return false;
}

bool Collision::CheckHit(const Sphere & sphere, const Capsule & capsule)
{
	Vector3 v = capsule.endPosition - capsule.startPosition;
	Vector3 n = Vector3::Nomalize(v);

	float t = Vector3::Dot(Vector3(sphere.position - capsule.startPosition), n);

	Vector3 vsn = n * t;
	Vector3 nPos = capsule.startPosition + vsn;

	float lengthLate = t / Vector3::Length(v);

	float distance;
	if (lengthLate < 0.0f) {
		distance = Vector3::Distance(sphere.position, capsule.startPosition) - capsule.radius;
	}
	else if (lengthLate <= 1.0f) {
		distance = Vector3::Distance(sphere.position, nPos) - capsule.radius;
	}
	else {
		distance = Vector3::Distance(sphere.position, capsule.endPosition) - capsule.radius;
	}

	if (distance <= sphere.radius) {
		return true;
	}
	else return false;
}

bool Collision::CheckHit(const Sphere& sphere, const Ray& ray, Vector3* inter, float* distance)
{
	Vector3 vec = ray.position - sphere.position;
	float b = Vector3::Dot(vec, ray.direction);
	float c = Vector3::Dot(vec, vec) - sphere.radius * sphere.radius;

	if (c > 0.0f && b > 0.0f) {
		return false;
	}

	float discr = b * b - c;
	if (discr < 0.0f) {
		return false;
	}

	float t = -b - sqrtf(discr);
	if (t < 0.0f) { t = 0.0f; }
	if (distance) {
		*distance = t;
	}

	if (inter) {
		*inter = ray.position + (ray.direction * t);
	}

	return true;
}
