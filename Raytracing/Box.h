#pragma once

#include "Point.h"
#include "Ray.h"

class Box
{
public:

	Box();
	Box(Point coordMax, Point coordMin);
	Box(Point coordMax, Point coordMin, int children[2]);

	Point coordMin, coordMax;
	vector<int> children;
	int trianglesIndexStart, trianglesIndexEnd;

	float rayIntersect(Ray ray);
	int computeBiggestAxis();
	void setTrianglesIndex(int trianglesIndexStart_, int trianglesIndexEnd_);
	void setChildren(int child1, int child2);
};

