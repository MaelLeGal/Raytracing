#include "Sphere.h"

Sphere::Sphere()
{
}

Sphere::Sphere(Point center, float radius) {
	this->center = center;
	this->radius = radius;
}

Sphere::Sphere(Point center, float radius, Material material) {
	this->center = center;
	this->radius = radius;
	this->material = material;
}


Sphere::~Sphere()
{
}
