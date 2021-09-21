#ifndef OBJECT_H
#define OBJECT_H

#pragma once
#include "Material.h"

class Object
{
public:
	Material material;

	Object();
	Object(Material material);
};

#endif // !OBJECT_H
