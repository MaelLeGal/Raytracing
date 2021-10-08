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

float Triangle::rayIntersect(Ray ray) {
	Vector edge1 = this->p2 - this->p1;
	Vector edge2 = this->p3 - this->p1;
	Direction h = ray.direction.cross(edge2);
	Vector s = ray.origin - this->p1;
	Direction q = s.cross(edge1);
	double a, f, u, v;
	a = edge1.dot(h);
	if (a > -0.01 && a < 0.01)
		return -1; // Le rayon est parallèle au triangle.
	f = 1.0 / a;
	u = f * (s.dot(h));
	if (u < 0.0 || u > 1.0) {
		return -1;
	}
	v = f * ray.direction.dot(q);
	if (v < 0.0 || u + v > 1.0) {
		return -1;
	}
	// On calcule t pour savoir ou le point d'intersection se situe sur la ligne.
	double t = f * edge2.dot(q);
	if (t > 0.01) // // Intersection avec le rayon
		return t;
	else // On a bien une intersection de droite, mais pas de rayon.
		return -1;
}

Direction Triangle::normal(Point intersect) {
	Direction u = p2 - p1;
	Direction v = p3 - p1;
	return Direction(u.cross(v));
}