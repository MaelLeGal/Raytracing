#ifndef MATERIAL_H
#define MATERIAL_H

#pragma once
#include "Vector.h"

enum class MaterialBehaviour {Diffuse, Glass, Mirror};

class Material
{
public:
	Vector material;
	MaterialBehaviour materialBehaviour;

	Material();
	Material(Vector material, MaterialBehaviour materialBehaviour);

};

#endif // MATERIAL_H

