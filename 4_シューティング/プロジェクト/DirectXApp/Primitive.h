#pragma once
#include"Vector3.h"

struct Sphere
{
	Vector3 position;
	float radius;
	
	Sphere(Vector3 position, float radius)
		:position(position), radius(radius)
	{}
};

struct Box
{
	Vector3 minPosition,
		maxPosition,
		radius,
		centerPosition;
		

	Box(Vector3 minPosition, Vector3 maxPosition)
		:minPosition(minPosition), maxPosition(maxPosition),
		radius((maxPosition - minPosition) / 2),
		centerPosition(minPosition + radius)
	{}
};

struct Capsule
{
	Vector3 startPosition,
		endPosition;
	float radius;

	Capsule(Vector3 startPosition, Vector3 endPosition, float radius)
		:startPosition(startPosition), endPosition(endPosition), radius(radius)
	{}
};

struct Line
{
	Vector3 startPosition = {};
	Vector3 endPosition = {};

	Line(Vector3 startpos, Vector3 endpos)
		:startPosition(startpos), endPosition(endpos)
	{}
};

struct Plane
{
	Vector3 position = {};
	Vector3 normal = { 0,1,0 };

	Plane(Vector3 position, Vector3 normal)
		:position(position), normal(normal)
	{}
};

struct Ray
{
	Vector3 position = {};
	Vector3 direction = {};

	Ray(Vector3 position, Vector3 direction)
		:position(position), direction(direction)
	{}
};