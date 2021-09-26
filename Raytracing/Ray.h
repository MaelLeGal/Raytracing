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


class Ray
{
public:
	
	Point origin;
	Direction direction;

	Ray();
	Ray(Point origin, Direction direction);
	~Ray();

};

Vector radiance(Ray ray, int depth);

float rayIntersectSphere(Ray ray, Sphere sphere);

tuple<float, Sphere> rayIntersectSpheres(Ray ray, vector<Sphere> spheres);

Point toneMap(Vector v);

Point rayTrace(int x, int y);

Vector mirror(Ray ray, Vector x, Direction normal, tuple<float, Object> intersect, Vector albedo, int depth);

Vector glass(Ray ray, Vector x, Direction normal, tuple<float, Object> intersect, Vector albedo, int depth);

#endif // !RAY_H
