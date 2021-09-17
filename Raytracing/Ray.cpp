#include "Ray.h"

Ray::Ray(Point origin, Direction direction)
{
	this->origin = origin;
	this->direction = direction;
}


Ray::~Ray()
{
}

Point radiance(Ray ray) {
	Sphere sphere = Sphere(Point({ 255,255,300 }), 200);
	vector<Sphere> spheres = { sphere, Sphere(Point({0,255,300}),100) };

	
	float intersect = rayIntersectSpheres(ray, spheres);
	if (intersect == -1){
		return Point({ 255,0,0 });
	}
	else {
		return Point({ intersect,intersect,intersect });
	}

	
}


float rayIntersectSphere(Ray ray, Sphere sphere) {

	Direction oc = sphere.center - ray.origin;
	float r2 = sphere.radius * sphere.radius;
	float a = ray.direction.dot(ray.direction);
	float b = -2 * ray.direction.dot(oc);
	float c = oc.dot(oc) - r2;

	//cout << "a : " << a << endl; //1
	//cout << "b : " << b << endl; //-20
	//cout << "c : " << c << endl; //99

	float delta = (b * b) - (4 * a * c);
	float t0 = -1;
	float t1 = -1;


	//cout << delta << endl;
	if (delta >= 0) {
		t0 = ((-b - sqrt(delta)) / (2 * a));
		t1 = ((-b + sqrt(delta)) / (2 * a));
	}

	//cout << t0 << endl;
	//cout << t1 << endl;

	if (t0 >= 0) return t0;
	if (t1 >= 0) return t1;

	return  -1;

}

float rayIntersectSpheres(Ray ray, vector<Sphere> spheres) {
	vector<float> intersections;
	for (auto sphere : spheres) {
		intersections.push_back(rayIntersectSphere(ray,sphere));
	}

	intersections.erase(remove(intersections.begin(), intersections.end(), -1), intersections.end());

	if (intersections.empty()) return -1;

	float intersection = *min_element(intersections.begin(), intersections.end());

	return intersection;


}

int main() {

	vector<int> dimensions = { 500,500 };
	vector<vector<vector<int>>> pixels(dimensions[0], vector<vector<int>>(dimensions[1]));
	


	cout << pixels.size() << endl;
	cout << pixels[0].size() << endl;
	cout << pixels[0][0].size() << endl;

	for (int i = 0; i < dimensions[0]; i++) {
		for (int j = 0; j < dimensions[1]; j++) {

			Ray ray = Ray(Point({ (float)j,(float)i,0 }), Direction({ 0,0,1 }));

			vector<float> pixel = radiance(ray).values; // Probleme int to float;
			//vector<int> pixel = { i%255,j%255,0 };
			pixels[i][j].insert(pixels[i][j].end(), pixel.begin(), pixel.end());
			//pixels[i][j].push_back(pixel);
		}
	}

	//Ray ray = Ray(Point({ 0,0,0 }), Direction({ 1,0,0 }));
	

	//float res = rayIntersect(ray, sphere);
	//cout << res << endl;

	cout << pixels[0][0].size() << endl;

	const char* filename = "first_image.ppm";

	createPPMImage(dimensions, pixels, filename);

};
