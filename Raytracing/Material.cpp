#include "Material.h"

Material::Material(){}

Material::Material(Vector material, MaterialBehaviour materialBehaviour) {
	this->material = material;
	this->materialBehaviour = materialBehaviour;
}

// The two parameters needs to be normalized
Direction reflect(Direction normal, Direction incomingRayDirection) {
	return Direction((2 * -normal.dot(incomingRayDirection) * normal + incomingRayDirection).normalize().values);
}
