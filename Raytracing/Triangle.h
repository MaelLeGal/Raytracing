#ifndef TRIANGLE_H
#define TRIANGLE_H

#pragma once
#include "Direction.h"
#include "Point.h"
#include "Vector.h"
#include "Object.h"
#include "Material.h"
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

	Direction normal();

};
#endif
