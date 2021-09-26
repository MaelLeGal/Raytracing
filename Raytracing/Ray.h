#ifndef RAY_H
#define RAY_H

#include "Direction.h"
#include "Point.h"
#include "Vector.h"
#include "CreationImagePPM.h"
#include "Sphere.h"
#include "Material.h"
#include "Object.h"
#include <tuple>
#include <random>
#include <iostream>


class Ray
{
public:
	
	Point origin;
	Direction direction;

	Ray();
	Ray(Point origin, Direction direction);
	~Ray();

};

Vector radiance(Ray ray, int depth, vector<Sphere> scene);

float rayIntersectSphere(Ray ray, Sphere sphere);

tuple<float, Sphere> rayIntersectSpheres(Ray ray, vector<Sphere> scene);

Point toneMap(Vector v);

Point rayTrace(int x, int y, vector<Sphere> scene);

Vector mirror(Ray ray, vector<Sphere> scene, Vector x, Direction normal, tuple<float, Sphere> intersect, Vector albedo, int depth);

Vector glass(Ray ray, vector<Sphere> scene, Vector x, Direction normal, tuple<float, Sphere> intersect, Vector albedo, int depth);

#endif // !RAY_H
