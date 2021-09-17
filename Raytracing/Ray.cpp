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
	Sphere sphere = Sphere(Point({ 255,255,1000 }), 150);
	vector<Sphere> spheres = { sphere, Sphere(Point({0,255,300}),100),Sphere(Point({5000+450,255,0}),5000),Sphere(Point({-5000 + 50,255,0}),5000), Sphere(Point({255,-5000+50,0}),5000), Sphere(Point({255,5000+450,0}),5000) };

	
	tuple<float,Sphere> intersect = rayIntersectSpheres(ray, spheres);
	if (get<0>(intersect) == -1){
		return Point({ 255,0,0 });
	}
	else {
		Point lightPosition = Point({ 255,255,255 });

		Vector x = (Vector)ray.origin + get<0>(intersect) * ray.direction;
		Direction directionToLight = Direction(((Vector)lightPosition-x).normalize().values);
		Direction normal = Direction(((Vector)get<1>(intersect).center - x).normalize().values);
		float lightCoef = abs(normal.dot(directionToLight)); //Add absolute value
		//Point enlightedPixel = toneMap(Vector({ lightCoef ,lightCoef ,lightCoef }));
		return Point({ 255 * lightCoef,255 * lightCoef,255 * lightCoef });
		//return enlightedPixel;
	}
}

Point toneMap(Vector v) {
	int max = *max_element(v.values.begin(), v.values.end());
	vector<float> values;
	for (auto val : v.values)
	{
		values.push_back((val/max)*255);
	}
	return Point(values);
}


float rayIntersectSphere(Ray ray, Sphere sphere) {

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

	//int max = *max_element(intersections.begin(), intersections.end());
	//float intersection = (*min_element(intersections.begin(), intersections.end()) / max) * 255;
	tuple<float, Sphere> intersection = *min_element(intersections.begin(), intersections.end(), [](const tuple<float, Sphere>& x, const tuple<float, Sphere>& y) { return get<0>(x) < get<0>(y);});

	return intersection;


}

int main() {

	vector<int> dimensions = { 500,500 };
	vector<vector<vector<int>>> pixels(dimensions[0], vector<vector<int>>(dimensions[1]));

	for (int i = 0; i < dimensions[0]; i++) {
		for (int j = 0; j < dimensions[1]; j++) {

			Ray ray = Ray(Point({ (float)j,(float)i,0 }), Direction({ 0,0,1 }));

			vector<float> pixel = radiance(ray).values; // Probleme int to float;
			//vector<int> pixel = { i%255,j%255,0 };
			pixels[i][j].insert(pixels[i][j].end(), pixel.begin(), pixel.end());
			//pixels[i][j].push_back(pixel);
		}
	}

	const char* filename = "first_image.ppm";

	createPPMImage(dimensions, pixels, filename);

};
