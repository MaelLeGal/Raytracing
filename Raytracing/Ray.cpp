#include "Ray.h"

using namespace std;

Ray::Ray() {

}

Ray::Ray(Point origin, Direction direction)
{
	this->origin = origin;
	this->direction = direction;
}


Ray::~Ray()
{
}

Vector radiance(Ray ray, int depth, vector<Sphere> scene) {

	if (depth == 5) {
		return Vector({ 1, 0, 1 });
	}
	
	tuple<float,Sphere> intersect = rayIntersectSpheres(ray, scene);
	if (get<0>(intersect) == -1){
		return Vector({ -1,-1,-1 });
	}
	else {
		
		Vector x;

		int numberOfRayToLight = 10;
		float r;
		float r2;
		Ray randomRayOnLight;
		Direction randomDirectionToLight;
		random_device rd;
		default_random_engine generator(rd());
		uniform_real_distribution<float> theta(0, 2 * M_PI);
		uniform_real_distribution<float> phi(0, M_PI);

		Vector pixelValue = Vector({ 0,0,0 });

		Sphere light = Sphere(Point({ 250,250,250 }), 60);
		Point lightPosition;
		Vector lightEmission;
		Direction normal;
		Direction directionToLight;
		Direction directionToLightNormalized;
		float lightDistance2;
		float lightCoef = 0;

		tuple<float, Sphere> tupleIntersectSphere;
		float intersectLight;
		Sphere sphereIntersect;
		bool canSeeLightSource;
		Vector visibility;

		float red;
		float green;
		float blue;
		Vector albedo;
		
		Direction reflectedDirection;
		Ray reflectedRay;
		Vector radianceReflectedRayPixel;
		
		tuple<float,Direction> transmittedDirection;
		Ray transmittedRay;
		Vector radianceTransmittedRayPixel;
		bool outside;
		float coef;
		Vector contribRefract;
		Vector contribReflect;
		
		lightPosition = Point({ 250,250,250 });
		lightEmission = Vector({0,50000,15000}); //Color and intensity of the lamp

		x = (Vector)ray.origin + get<0>(intersect) * ray.direction; // Intersection Point

		normal = Direction((x - (Vector)get<1>(intersect).center).normalize().values);

		//Sphere color
		albedo = get<1>(intersect).material.material;

		switch (get<1>(intersect).material.materialBehaviour) { //TODO Make function for each case and call it
			case MaterialBehaviour::Diffuse:
				directionToLight = Direction(((Vector)light.center - x).values);
				x = x + directionToLight * 0.01; // Added an Epsilon for our object not to cast shadow on themselves

				for (int i = 0; i < numberOfRayToLight; i++) {
					r = theta(generator);
					r2 = phi(generator);

					randomDirectionToLight = Direction(((Vector(light.center.values) + Vector({ light.radius * cos(r) * sin(r2) , light.radius * sin(r) * sin(r2), light.radius*cos(r2)})) - x).values);

					randomRayOnLight = Ray(Point(x.values), randomDirectionToLight);

					directionToLightNormalized = Direction(randomRayOnLight.direction.normalize().values);
					lightDistance2 = randomRayOnLight.direction.dot(randomRayOnLight.direction);
					lightCoef += normal.dot(directionToLightNormalized / lightDistance2) < 0 ? 0 : normal.dot(directionToLightNormalized / lightDistance2);

					tupleIntersectSphere = rayIntersectSpheres(Ray(Point(x.values), directionToLightNormalized), scene);
					intersectLight = get<0>(tupleIntersectSphere);
					sphereIntersect = get<1>(tupleIntersectSphere);
					canSeeLightSource = (intersectLight == -1 ? true : ((intersectLight * intersectLight) > lightDistance2));
					visibility = canSeeLightSource ? Vector({ 1,1,1 }) : Vector({ 0,0,0 });

					pixelValue = pixelValue + Vector({visibility.values[0] * lightEmission.values[0] * lightCoef * albedo.values[0] ,
					visibility.values[1] * lightEmission.values[1] * lightCoef * albedo.values[1],
					visibility.values[2] * lightEmission.values[2] * lightCoef * albedo.values[2] });
				}
				return pixelValue / numberOfRayToLight;
				break;

			case MaterialBehaviour::Mirror:

				return mirror(ray, scene, x, normal, intersect, albedo, depth);
				break; //optional

			case MaterialBehaviour::Glass:

				return glass(ray, scene, x, normal, intersect, albedo, depth);
				break; //optional

			 // you can have any number of case statements.
			default: //Optional
				cout << "Default for some reason" << endl;
				return Vector({ -1,-1,-1 });
		}
	}
}

Point toneMap(Vector v) {
	int min = *min_element(v.values.begin(), v.values.end());
	vector<float> values;
	for (auto val : v.values)
	{
		float value = floor(pow(val, 1.0 / 2.2) * 255);
		value = value > 255 ? 255 : value;
		value = value < 0 ? 0 : value;
		values.push_back(value);
	}
	return Point(values);
}

float rayIntersectSphere(Ray ray, Sphere sphere) { //Change to return c++2017 optional


	Direction oc = sphere.center - ray.origin;
	float r2 = sphere.radius * sphere.radius;
	float a = 1; //ray.direction.dot(ray.direction); // a = 1 because ray.diraction.dot(ray.direction) = 1 when ray.direction is normalized
	float b = -ray.direction.dot(oc);
	float c = oc.dot(oc) - r2;

	float delta = (b * b) - c; //((2*b) * (2*b)) - (4 * a * c); //(b * b) - (4 * a * c);
	float sqrt_delta = sqrt(delta);
	float t0 = -1;
	float t1 = -1;

	if (delta >= 0) {
		t0 = (-b - sqrt_delta); //((-b - sqrt_delta) / (2 * a));
		t1 = (-b + sqrt_delta); //((-b + sqrt_delta) / (2 * a));
	}

	if (t0 >= 0) return t0;
	if (t1 >= 0) return t1;

	return  -1;

}

tuple<float, Sphere> rayIntersectSpheres(Ray ray, vector<Sphere> scene) {
	vector<tuple<float, Sphere>> intersections;
	for (Sphere sphere : scene) {
		intersections.push_back(make_tuple(rayIntersectSphere(ray,sphere),sphere));
	}

	intersections.erase(remove_if(intersections.begin(), intersections.end(), [](const tuple<float,Sphere>& x) -> bool {return get<0>(x) == -1;}), intersections.end());

	if (intersections.empty()) return make_tuple(-1,Sphere());

	tuple<float, Sphere> intersection = *min_element(intersections.begin(), intersections.end(), [](const tuple<float, Sphere>& x, const tuple<float, Sphere>& y) { return get<0>(x) < get<0>(y);});

	return intersection;


}

Point rayTrace(int x, int y, vector<Sphere> scene) {
	
	int numberOfRayPerPixel = 10;

	Vector pointNearPlane;
	Vector pointNearPlaneMoved;
	Vector pointFarPlane;

	Direction cameraDirection;

	float fov = 1.001;

	pointNearPlane = Vector({ (float)y,(float)x,0 });
	pointNearPlaneMoved = pointNearPlane - Vector({ 250,250,0 }); //Move the point on the plane -250:250
	pointFarPlane = Vector({ pointNearPlaneMoved.values[0] * fov,pointNearPlaneMoved.values[1] * fov,1 }); //Apply the fov

	cameraDirection = Direction((pointFarPlane - pointNearPlaneMoved).normalize().values);

	Ray ray = Ray(Point(pointNearPlane.values), cameraDirection);

	//vector<Vector> contribs = vector<Vector>();
	Vector contrib = Vector({0,0,0});
	Vector color;

	for (int i = 0; i < numberOfRayPerPixel; i++) {
		color = radiance(ray, 0, scene);
		if (contrib.values[0] != -1) {
			contrib = contrib + color;
		}
	}
	contrib = contrib / numberOfRayPerPixel;

	return toneMap(contrib);

	/*Vector color = radiance(ray, 0, scene);
	if (color.values[0] == -1) {
		return Point({ 0,0,0 });
	}
	else {
		return toneMap(color);
	}*/
}

Vector mirror(Ray ray, vector<Sphere> scene, Vector x, Direction normal, tuple<float, Sphere> intersect, Vector albedo, int depth) {

	Direction reflectedDirection;
	Ray reflectedRay;
	Vector radianceReflectedRayPixel;

	reflectedDirection = reflect(normal, ray.direction);
	reflectedRay = Ray(Point((x + 0.01 * reflectedDirection).values), reflectedDirection);
	radianceReflectedRayPixel = (Vector)radiance(reflectedRay, depth + 1, scene);
	if (radianceReflectedRayPixel.values[0] == -1) {
		return Vector({ 0,0,0 });
	}
	else {
		return Vector({ radianceReflectedRayPixel.values[0] * albedo.values[0], radianceReflectedRayPixel.values[1] * albedo.values[1], radianceReflectedRayPixel.values[2] * albedo.values[2] });
	}
}

Vector glass(Ray ray, vector<Sphere> scene, Vector x, Direction normal, tuple<float, Sphere> intersect, Vector albedo, int depth) {

	tuple<float, Direction> transmittedDirection;
	Ray transmittedRay;
	Vector radianceTransmittedRayPixel;
	bool outside;
	float coef;
	Vector contribRefract;

	Direction reflectedDirection;
	Ray reflectedRay;
	Vector radianceReflectedRayPixel;
	Vector contribReflect;

	outside = ray.direction.dot(normal) < 0;
	transmittedDirection = refract(get<1>(intersect).material.indiceOfRefraction, normal, ray.direction, outside);
	coef = get<0>(transmittedDirection);
	if (coef == -1) {
		return mirror(ray, scene, x, normal, intersect, albedo, depth);
	}
	else {

		random_device rd;
		default_random_engine generator(rd());
		uniform_real_distribution<float> distribution(0, 1);
		float r = distribution(generator);

		if (r < coef) {
			transmittedRay = Ray(Point((x + 0.03 * get<1>(transmittedDirection)).values), get<1>(transmittedDirection));
			radianceTransmittedRayPixel = (Vector)radiance(transmittedRay, depth + 1, scene);
			if (radianceTransmittedRayPixel.values[0] == -1) {
				contribRefract = Vector({ 0,0,0 });
			}
			else {
				contribRefract = Vector({ radianceTransmittedRayPixel.values[0] * albedo.values[0], radianceTransmittedRayPixel.values[1] * albedo.values[1], radianceTransmittedRayPixel.values[2] * albedo.values[2] });
			}
			return (1 / coef) * contribRefract * coef;
		}
		else {

			contribReflect = mirror(ray, scene, x, normal, intersect, albedo, depth);
			return (1 / (1 - coef)) * contribReflect * (1 - coef);
		}
	}
}

int main() {

	vector<int> dimensions = { 500,500 };
	vector<vector<vector<int>>> pixels(dimensions[0], vector<vector<int>>(dimensions[1]));

	vector<Sphere> scene = {																		// Need to be a parameter of radiance
		Sphere(Point({5000 + 500,250,0}),5000, Material(Vector({1,1,0}), MaterialBehaviour::Diffuse)), //Right
		Sphere(Point({-5000,250,0}),5000, Material(Vector({0,1,1}), MaterialBehaviour::Diffuse)), //Left
		Sphere(Point({250,-5000,0}),5000, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse)), //Top
		Sphere(Point({250,5000 + 500,0}),5000, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse)), //Bottom
		Sphere(Point({250,250 ,5000 + 500}),5000, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse)), // Back

		Sphere(Point({150,350,250}),80, Material(Vector({1,1,1}), MaterialBehaviour::Mirror)),

		Sphere(Point({350,350,250}),80, Material(Vector({1,1,1}), MaterialBehaviour::Glass, 2.4))
	};

	for (int i = 0; i < dimensions[0]; i++) {
		for (int j = 0; j < dimensions[1]; j++) {

			vector<float> pixel = rayTrace(i, j, scene).values;

			pixels[i][j].insert(pixels[i][j].end(), pixel.begin(), pixel.end());

		}
	}

	cout << "Loop Done" << endl;

	const char* filename = "first_image.ppm";

	createPPMImage(dimensions, pixels, filename);

};
