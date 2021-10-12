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

float Sphere::rayIntersect(Ray ray) {

	Direction oc = this->center - ray.origin;
	float r2 = this->radius * this->radius;
	float a = 1; //ray.direction.dot(ray.direction); // a = 1 because ray.diraction.dot(ray.direction) = 1 when ray.direction is normalized
	float b = -ray.direction.dot(oc);
	float c = oc.dot(oc) - r2;

	float delta = (b * b) - c; //((2*b) * (2*b)) - (4 * a * c); //(b * b) - (4 * a * c);
	float sqrt_delta = sqrt(delta);
	float t0 = -1;
	float t1 = -1;

	if (delta >= 0) {
		t0 = (-b - sqrt_delta); //((-b - sqrt_delta) / (2 * a));
		t1 = (-b + sqrt_delta); //((-b + sqrt_delta) / (2 * a));
	}

	if (t0 >= 0) return t0;
	if (t1 >= 0) return t1;

	return  -1;
}

Direction Sphere::normal(Point intersect) {
	return Direction(intersect - this->center);
}

tuple<Point, Point> Sphere::getEnglobingCube() {
	Point maxCoord = Point(this->center.data[1] + this->radius, this->center.data[2] + this->radius, this->center.data[2] + this->radius);
	Point minCoord = Point(this->center.data[1] - this->radius, this->center.data[2] - this->radius, this->center.data[2] - this->radius);
	return make_tuple(maxCoord, minCoord);
};
