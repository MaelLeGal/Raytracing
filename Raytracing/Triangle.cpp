#include "Triangle.h"

Triangle::Triangle()
{
}

Triangle::Triangle(Point p1_, Point p2_, Point p3_) {
	this->p1 = p1_;
	this->p2 = p2_;
	this->p3 = p3_;
}

Triangle::Triangle(Point p1_, Point p2_, Point p3_, Material material) {
	this->p1 = p1_;
	this->p2 = p2_;
	this->p3 = p3_;
	this->material = material;
}


Triangle::~Triangle()
{
}

Direction Triangle::normal() {
	Direction u = p2 - p1;
	Direction v = p3 - p1;
	return Direction(u.cross(v));
}