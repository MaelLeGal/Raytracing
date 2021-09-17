#pragma once
#include "Direction.h";
#include "Point.h";
#include "Vector.h";

class Sphere
{
public:

	Point center;
	float radius;

	Sphere();
	Sphere(Point center, float radius);
	~Sphere();
};

