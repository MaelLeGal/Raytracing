#pragma once
#include "Direction.h";
#include "Point.h";
#include "Vector.h";
#include "Object.h";

class Sphere : public Object
{
public:

	Point center;
	float radius;

	Sphere();
	Sphere(Point center, float radius);
	Sphere(Point center, float radius, Material material);
	~Sphere();
};

