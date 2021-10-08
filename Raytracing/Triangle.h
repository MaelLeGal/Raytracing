#ifndef TRIANGLE_H
#define TRIANGLE_H

#pragma once
#include "Object.h"

class Triangle : public Object
{
public:
		
	Point p1;
	Point p2;
	Point p3;

	Triangle();
	Triangle(Point p1_, Point p2_, Point p3_);
	Triangle(Point p1_, Point p2_, Point p3_, Material material);
	~Triangle();

	float rayIntersect(Ray ray) override;
	Direction normal(Point intersect) override;

};
#endif
