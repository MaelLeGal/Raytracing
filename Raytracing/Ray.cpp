#include "Ray.h"

using namespace std;

Ray::Ray(Point origin, Direction direction)
{
	this->origin = origin;
	this->direction = direction;
}


Ray::~Ray()
{
}

Point radiance(Ray ray) {
	//Sphere sphere = Sphere(Point({ 250,250,1000 }), 150, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse));
	vector<Sphere> spheres = {																		// Need to be a parameter of radiance
		Sphere(Point({5000+500,250,0}),5000, Material(Vector({1,1,0}), MaterialBehaviour::Diffuse)), //Right
		Sphere(Point({-5000,250,0}),5000, Material(Vector({0,1,1}), MaterialBehaviour::Diffuse)), //Left
		Sphere(Point({250,-5000,0}),5000, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse)), //Top
		Sphere(Point({250,5000+500,0}),5000, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse)), //Bottom
		Sphere(Point({250,250 ,5000 + 500}),5000, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse)), // Back

		Sphere(Point({150,350,350}),80, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse)),
		
		Sphere(Point({350,350,350}),80, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse))
	}; 

	vector<Sphere> scene = {
		Sphere(Point({5000 + 500,250,0}),5000, Material(Vector({1,1,0}), MaterialBehaviour::Diffuse)), //Right
		Sphere(Point({-5000,250,0}),5000, Material(Vector({0,1,1}), MaterialBehaviour::Diffuse)), //Left
		Sphere(Point({250,-5000,0}),5000, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse)), //Top
		Sphere(Point({250,5000 + 500,0}),5000, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse)), //Bottom
		Sphere(Point({250,250 ,5000 + 500}),5000, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse)), // Back
	};

	

	
	tuple<float,Sphere> intersect = rayIntersectSpheres(ray, spheres);
	if (get<0>(intersect) == -1){
		return Point({ 255,255,255 });
	}
	else {
		Point lightPosition = Point({ 250,250,250 });
		Vector lightEmission = Vector({50000,50000,50000}); //Color and intensity of the lamp

		Vector x = (Vector)ray.origin + get<0>(intersect) * ray.direction; // Intersection Point
		Direction directionToLight = Direction(((Vector)lightPosition-x).values);
		
		x = x + directionToLight * 0.01; // Added an Epsilon for our object not to cast shadow on themselves

		//Light
		Direction normal = Direction((x - (Vector)get<1>(intersect).center).normalize().values);
		Direction directionToLightNormalized = Direction(directionToLight.normalize().values);
		float lightDistance2 = directionToLight.dot(directionToLight);
		float lightCoef = normal.dot(directionToLightNormalized / lightDistance2) < 0 ? 0 : normal.dot(directionToLightNormalized / lightDistance2); //Attenuation of the light by the distance to it.
		
		// Shadow
		tuple<float, Sphere> tupleIntersectSphere = rayIntersectSpheres(Ray(Point(x.values), directionToLightNormalized), spheres);
		float intersectLight = get<0>(tupleIntersectSphere);
		Sphere sphereIntersect = get<1>(tupleIntersectSphere);
		bool canSeeLightSource = (intersectLight == -1 ? true : ((intersectLight * intersectLight) > lightDistance2));
		Vector visibility = canSeeLightSource ? Vector({1,1,1}) : Vector({ 0,0,0 });

		//Sphere color
		float red = get<1>(intersect).material.material.values[0];
		float green = get<1>(intersect).material.material.values[1];
		float blue = get<1>(intersect).material.material.values[2];

		return toneMap(Vector({visibility.values[0] * lightEmission.values[0] * lightCoef * red ,
			visibility.values[1] * lightEmission.values[1] * lightCoef * green,
			visibility.values[2] * lightEmission.values[2] * lightCoef * blue }));
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
	float a = ray.direction.dot(ray.direction);
	float b = -2 * ray.direction.dot(oc);
	float c = oc.dot(oc) - r2;

	float delta = (b * b) - (4 * a * c);
	float t0 = -1;
	float t1 = -1;

	if (delta >= 0) {
		t0 = ((-b - sqrt(delta)) / (2 * a));
		t1 = ((-b + sqrt(delta)) / (2 * a));
	}

	if (t0 >= 0) return t0;
	if (t1 >= 0) return t1;

	return  -1;

}

tuple<float, Sphere> rayIntersectSpheres(Ray ray, vector<Sphere> spheres) {
	vector<tuple<float, Sphere>> intersections;
	for (auto sphere : spheres) {
		intersections.push_back(make_tuple(rayIntersectSphere(ray,sphere),sphere));
	}

	intersections.erase(remove_if(intersections.begin(), intersections.end(), [](const tuple<float,Sphere>& x) -> bool {return get<0>(x) == -1;}), intersections.end());

	if (intersections.empty()) return make_tuple(-1,Sphere());

	tuple<float, Sphere> intersection = *min_element(intersections.begin(), intersections.end(), [](const tuple<float, Sphere>& x, const tuple<float, Sphere>& y) { return get<0>(x) < get<0>(y);});

	return intersection;


}

int main() {

	vector<int> dimensions = { 500,500 };
	vector<vector<vector<int>>> pixels(dimensions[0], vector<vector<int>>(dimensions[1]));

	Vector pointNearPlane;
	Vector pointNearPlaneMoved;
	Vector pointFarPlane;

	Direction cameraDirection;

	float fov = 1.001;

	for (int i = 0; i < dimensions[0]; i++) {
		for (int j = 0; j < dimensions[1]; j++) {
			
			pointNearPlane = Vector({ (float)j,(float)i,0 });
			pointNearPlaneMoved = pointNearPlane - Vector({ 250,250,0 }); //Move the point on the plane -250:250
			pointFarPlane = Vector({ pointNearPlaneMoved.values[0] * fov,pointNearPlaneMoved.values[1] * fov,1 }); //Apply the fov

			cameraDirection = Direction((pointFarPlane - pointNearPlaneMoved).normalize().values);

			Ray ray = Ray(Point(pointNearPlane.values), cameraDirection);

			vector<float> pixel = radiance(ray).values; // Probleme int to float;

			pixels[i][j].insert(pixels[i][j].end(), pixel.begin(), pixel.end());

		}
	}

	cout << "Loop Done" << endl;

	const char* filename = "first_image.ppm";

	createPPMImage(dimensions, pixels, filename);

};
