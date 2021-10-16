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
	//cout << "Triangle ray intersect" << endl;
	Vector edge1 = this->p2 - this->p1;
	Vector edge2 = this->p3 - this->p1;
	Direction h = ray.direction.cross(edge2);
	Vector s = ray.origin - this->p1;
	Direction q = s.cross(edge1);
	double a, f, u, v;
	a = edge1.dot(h);
	//cout << "a : " << a << endl;
	if (a > -0.01 && a < 0.01)
		return -1; // Le rayon est parallèle au triangle.
	f = 1.0 / a;
	u = f * (s.dot(h));
	//cout << "f : " << f << endl;
	//cout << "u : " << u << endl;
	if (u < 0.0 || u > 1.0) {
		return -1;
	}
	v = f * ray.direction.dot(q);
	//cout << "v : " << v << endl;
	//cout << "u+v : " << u + v << endl;
	if (v < 0.0 || u + v > 1.0) {
		return  -1;
	}
	// On calcule t pour savoir ou le point d'intersection se situe sur la ligne.
	double t = f * edge2.dot(q);

	//cout << "Intersection triangle detected : " << t << endl;

	if (t > 0.01) // // Intersection avec le rayon
		return t;
	else // On a bien une intersection de droite, mais pas de rayon.
		return -1;

	/*Sphere* testSphere = new Sphere(Point(this->p1.data), 5, Material(Vector({1,0,1}), MaterialBehaviour::Diffuse));
	return testSphere->rayIntersect(ray);*/
}

Direction Triangle::normal(Point intersect) {
	Direction u = p2 - p1;
	Direction v = p3 - p1;
	return Direction(u.cross(v));
}

tuple<Point, Point> Triangle::getEnglobingCube() {
	float maxX = max({ this->p1.data[0], this->p2.data[0], this->p3.data[0] });
	float maxY = max({this->p1.data[1], this->p2.data[1], this->p3.data[1]});
	float maxZ = max({ this->p1.data[2], this->p2.data[2], this->p3.data[2] });

	float minX = min({ this->p1.data[0], this->p2.data[0], this->p3.data[0] });
	float minY = min({ this->p1.data[1], this->p2.data[1], this->p3.data[1] });
	float minZ = min({ this->p1.data[2], this->p2.data[2], this->p3.data[2] });

	Point maxCoord = Point(maxX, maxY, maxZ);
	Point minCoord = Point(minX, minY, minZ);
	return make_tuple(maxCoord, minCoord);
	//return make_tuple(Point(-1, -1, -1), Point(-1, -1, -1));
};