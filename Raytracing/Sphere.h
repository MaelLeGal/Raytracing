#ifndef SPHERE_H
#define SPHERE_H

#pragma once
#include "Object.h"

class Sphere : public Object
{
public:

	Point center;
	float radius;

	Sphere();
	Sphere(Point center, float radius);
	Sphere(Point center, float radius, Material material);
	~Sphere();

	float rayIntersect(Ray ray) override;
	Direction normal(Point intersect) override;
	tuple<Point, Point> getEnglobingCube() override;
};
#endif // !SPHERE_H