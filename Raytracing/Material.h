#ifndef MATERIAL_H
#define MATERIAL_H

#pragma once
#include "Vector.h"
#include "Direction.h"

enum class MaterialBehaviour {Diffuse, Glass, Mirror};

class Material
{
public:
	Vector material;
	MaterialBehaviour materialBehaviour;

	Material();
	Material(Vector material, MaterialBehaviour materialBehaviour);
};

Direction reflect(Direction normal, Direction incomingRayDirection);

#endif // MATERIAL_H

