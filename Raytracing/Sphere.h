#ifndef SPHERE_H
#define SPHERE_H

#pragma once
#include "Direction.h"
#include "Point.h"
#include "Vector.h"
#include "Object.h"
#include "Material.h"

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
#endif // !SPHERE_H