#include "Material.h"

Material::Material(){}

Material::Material(Vector material, MaterialBehaviour materialBehaviour) {
	this->material = material;
	this->materialBehaviour = materialBehaviour;
}

Material::Material(Vector material, MaterialBehaviour materialBehaviour, float indiceOfRefraction) {
	this->material = material;
	this->materialBehaviour = materialBehaviour;
	this->indiceOfRefraction = indiceOfRefraction;
}

// The two parameters needs to be normalized
Direction reflect(Direction normal, Direction incomingRayDirection) {
	return Direction((2 * -normal.dot(incomingRayDirection) * normal + incomingRayDirection).normalize());
}

tuple<float, Direction> refract(float indiceOfRefraction, Direction normal, Direction incomingRayDirection, bool outside) {

	indiceOfRefraction = outside ? 1 / indiceOfRefraction : indiceOfRefraction;
	normal = outside ? normal : Direction((-1 * normal).normalize());
	
	float cos_t1 = incomingRayDirection.dot(normal);
	float cos_t2_2 = 1 - indiceOfRefraction * indiceOfRefraction * (1 - cos_t1 * cos_t1);
	
	if (cos_t2_2 < 0) {
		return make_tuple(-1, Direction());
	}
	else {
		Direction tdir = Direction(((incomingRayDirection * indiceOfRefraction) - (normal * (cos_t1 * indiceOfRefraction + sqrt(cos_t2_2)))).normalize());
	
		float r0 = powf(((indiceOfRefraction - 1) / (indiceOfRefraction + 1)), 2);

		float cosTheta = 1 - (outside ? -cos_t1 : abs(tdir.dot(normal)));

		float reflectCoef = r0 + ((1 - r0) * powf(cosTheta, 5));
		return make_tuple(1 - reflectCoef, tdir);
	}
}
