#include "Material.h"

Material::Material(){}

Material::Material(Vector material, MaterialBehaviour materialBehaviour) {
	this->material = material;
	this->materialBehaviour = materialBehaviour;
}
