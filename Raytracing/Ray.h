#ifndef RAY_H
#define RAY_H

#include "Direction.h"
#include "Point.h"
#include "Vector.h"
#include "CreationImagePPM.h"
#include "Sphere.h"
#include "Material.h"
#include <tuple>


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

#endif // !RAY_H
