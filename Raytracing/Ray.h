//#include "CreationImagePPM.cpp";
//#include "Direction.h";
//#include "Point.h";
//#include "Vector.h";
//#include "Sphere.h";

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

	Ray(Point origin, Direction direction);
	~Ray();

};

Point radiance(Ray ray);

float rayIntersectSphere(Ray ray, Sphere sphere);

tuple<float, Sphere> rayIntersectSpheres(Ray ray, vector<Sphere> spheres);

Point toneMap(Vector v);

