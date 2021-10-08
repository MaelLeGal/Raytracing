#pragma once

#define _USE_MATH_DEFINES

#include <tuple>
#include <random>
#include <iostream>
#include <math.h>
#include "Point.h"
#include "Direction.h"
#include "Object.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Ray.h"
#include "CreationImagePPM.h"
#include "MeshFileParser.h"

Vector radiance(Ray ray, int depth, vector<Object> scene);

tuple<float, Object> rayIntersectObjects(Ray ray, vector<Object*> scene);

Point rayTrace(int x, int y, vector<Object*> scene);

Vector diffuse(Ray ray, int numberOfRayToLight, vector<Object*> scene, Point x, Direction normal, tuple<float, Object> intersect, Vector albedo, Sphere light, Vector lightEmission, int depth);

Vector mirror(Ray ray, vector<Object*> scene, Point x, Direction normal, tuple<float, Object> intersect, Vector albedo, int depth);

Vector glass(Ray ray, vector<Object*> scene, Point x, Direction normal, tuple<float, Object> intersect, Vector albedo, int depth);

Point toneMap(Vector v);

tuple<Direction, float> sample_cosinus(float u, float v);

tuple<Direction, Direction> make_base(Direction normal);

Direction rotate_vector(Direction normal, Direction indirectDirection);