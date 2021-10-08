#ifndef OBJECT_H
#define OBJECT_H

#pragma once
#include "Material.h"
#include "Point.h"
#include "Ray.h"

class Object
{
public:
	Material material;

	Object();
	Object(Material material);

	float virtual rayIntersect(Ray ray) { return -1; };
	Direction virtual normal(Point intersect) {return Direction(-1,-1,-1);};
};

#endif // !OBJECT_H
