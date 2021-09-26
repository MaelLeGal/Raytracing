#ifndef MATERIAL_H
#define MATERIAL_H

#pragma once
#include "Vector.h"
#include "Direction.h"
#include <tuple>
#include <random>

enum class MaterialBehaviour {Diffuse, Glass, Mirror};

class Material
{
public:
	Vector material;
	MaterialBehaviour materialBehaviour;
	float indiceOfRefraction = 1;

	Material();
	Material(Vector material, MaterialBehaviour materialBehaviour);
	Material(Vector material, MaterialBehaviour materialBehaviour, float indiceOfRefraction);
};

Direction reflect(Direction normal, Direction incomingRayDirection);

tuple<float, Direction> refract(float indiceOfRefraction, Direction normal, Direction incomingRayDirection, bool outside);

#endif // MATERIAL_H

