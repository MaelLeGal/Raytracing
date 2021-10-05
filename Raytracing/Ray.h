#ifndef RAY_H
#define RAY_H
#define _USE_MATH_DEFINES

#include "Direction.h"
#include "Point.h"
#include "Vector.h"
#include "CreationImagePPM.h"
#include "MeshFileParser.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Material.h"
#include "Object.h"
#include <tuple>
#include <random>
#include <iostream>
#include <math.h>


class Ray
{
public:
	
	Point origin;
	Direction direction;

	Ray();
	Ray(Point origin, Direction direction);
	~Ray();

};

// TODO use generic types

// Spheres
Vector radiance(Ray ray, int depth, vector<Sphere> scene);

float rayIntersectSphere(Ray ray, Sphere sphere);

tuple<float, Sphere> rayIntersectSpheres(Ray ray, vector<Sphere> scene); 

Point rayTrace(int x, int y, vector<Sphere> scene);

Vector diffuse(Ray ray, int numberOfRayToLight, vector<Sphere> scene, Point x, Direction normal, tuple<float, Sphere> intersect, Vector albedo, Sphere light, Vector lightEmission, int depth);

Vector mirror(Ray ray, vector<Sphere> scene, Point x, Direction normal, tuple<float, Sphere> intersect, Vector albedo, int depth);

Vector glass(Ray ray, vector<Sphere> scene, Point x, Direction normal, tuple<float, Sphere> intersect, Vector albedo, int depth);

// Triangles

Vector radiance(Ray ray, int depth, vector<Triangle> scene);

float rayIntersectTriangle(Ray, Triangle triangle);

tuple<float, Triangle> rayIntersectTriangles(Ray ray, vector<Triangle> scene);

Point rayTrace(int x, int y, vector<Triangle> scene);

Vector diffuse(Ray ray, int numberOfRayToLight, vector<Triangle> scene, Point x, Direction normal, tuple<float, Triangle> intersect, Vector albedo, Sphere light, Vector lightEmission, int depth);

Vector mirror(Ray ray, vector<Triangle> scene, Point x, Direction normal, tuple<float, Triangle> intersect, Vector albedo, int depth);

Vector glass(Ray ray, vector<Triangle> scene, Point x, Direction normal, tuple<float, Triangle> intersect, Vector albedo, int depth);

// TOOLS
Point toneMap(Vector v);

tuple<Direction,float> sample_cosinus(float u, float v);

tuple<Direction, Direction> make_base(Direction normal);

Direction rotate_vector(Direction normal, Direction indirectDirection);

#endif // !RAY_H
