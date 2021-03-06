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


/*Vector radiance(Ray ray, int depth, vector<Object> scene) {

	float r;
	float coefRR = depth == 0 ? 1 : (float)0.5;
	//random_device rd;
	//default_random_engine generator(rd());
	//uniform_real_distribution<float> urd(0,1);
	//r = urd(generator);
	//srand(time(nullptr));
	r = ((float)rand() / (RAND_MAX));

	if (r > coefRR) {
		return Vector({ 0,0,0 });
	}

	if (depth == 5) {
		return Vector({ 0, 0, 0 });
	}

	tuple<float, Object> intersect = rayIntersectObjects(ray, scene);
	if (get<0>(intersect) == -1) {
		return Vector({ -1,-1,-1 });
	}
	else {

		Point x;

		int numberOfRayToLight = 2;
		Sphere light = Sphere(Point({ 125,10,125 }), 24);
		Point lightPosition;
		Vector lightEmission;

		Direction normal;

		Vector albedo;

		lightPosition = Point({ 125,10,125 });
		lightEmission = Vector({ 2000,2000,2000 }); //Color and intensity of the lamp

		x = ray.origin + get<0>(intersect) * ray.direction; // Intersection Point

		normal = Direction((get<1>(intersect).normal(x)).normalize());

		//Sphere color
		albedo = get<1>(intersect).material.material;

		switch (get<1>(intersect).material.materialBehaviour) { //TODO Make function for each case and call it
		case MaterialBehaviour::Diffuse:

			return (1 / coefRR) * diffuse(ray, numberOfRayToLight, scene, x, normal, intersect, albedo, light, lightEmission, depth);
			break;

		case MaterialBehaviour::Mirror:

			return (1 / coefRR) * mirror(ray, scene, x, normal, intersect, albedo, depth);
			break; //optional

		case MaterialBehaviour::Glass:

			return (1 / coefRR) * glass(ray, scene, x, normal, intersect, albedo, depth);
			break; //optional

		 // you can have any number of case statements.
		default: //Optional
			cout << "Default for some reason" << endl;
			return Vector({ -1,-1,-1 });
		}
	}

}*/

/*tuple<float, Object> rayIntersectObjects(Ray ray, vector<Object> scene) {
	int numberOfObject = scene.size();
	vector<tuple<float, Object>> intersections(numberOfObject);
	//for (Sphere sphere : scene) {
	//	intersections.push_back(make_tuple(rayIntersectSphere(ray,sphere),sphere));
	//}

	for (int i = 0; i < numberOfObject; i++) {
		intersections[i] = make_tuple(scene[i].rayIntersect(&ray), scene[i]);
	}

	intersections.erase(remove_if(intersections.begin(), intersections.end(), [](const tuple<float, Object>& x) -> bool {return get<0>(x) == -1;}), intersections.end());

	if (intersections.empty()) return make_tuple(-1, Object());

	tuple<float, Object> intersection = *min_element(intersections.begin(), intersections.end(), [](const tuple<float, Object>& x, const tuple<float, Object>& y) { return get<0>(x) < get<0>(y);});

	return intersection;

}*/

/*Point rayTrace(int x, int y, vector<Object> scene) {
	int numberOfRayPerPixel = 5;

	Vector pointNearPlane;
	Vector pointNearPlaneMoved;
	Vector pointFarPlane;

	Direction cameraDirection;

	float fov = (float)1.001;

	pointNearPlane = Vector((float)y, (float)x, 0);
	pointNearPlaneMoved = pointNearPlane - Vector(125, 125, 0); //Move the point on the plane -250:250
	pointFarPlane = Vector(pointNearPlaneMoved.data[0] * fov, pointNearPlaneMoved.data[1] * fov, 1);//Vector({ pointNearPlaneMoved.values[0] * fov,pointNearPlaneMoved.values[1] * fov,1 }); //Apply the fov

	cameraDirection = Direction((pointFarPlane - pointNearPlaneMoved).normalize());

	Ray ray = Ray(Point(pointNearPlane.data), cameraDirection);

	Vector contrib = Vector({ 0,0,0 });
	Vector color;

	for (int i = 0; i < numberOfRayPerPixel; i++) {
		color = radiance(ray, 0, scene);
		if (contrib.data[0] != -1) {
			contrib = contrib + color;
		}
	}
	contrib = contrib / (float)numberOfRayPerPixel;

	return toneMap(contrib);
}*/

/*Vector diffuse(Ray ray, int numberOfRayToLight, vector<Object> scene, Point x, Direction normal, tuple<float, Object> intersect, Vector albedo, Sphere light, Vector lightEmission, int depth) {
	float r;
	float r2;
	Ray randomRayOnLight;
	Direction randomDirectionToLight;
	random_device rd;
	minstd_rand generator(rd());
	uniform_real_distribution<float> theta(0, 2 * M_PI);
	uniform_real_distribution<float> phi(0, M_PI);

	Direction directionToLight;
	Direction directionToLightNormalized;
	float lightDistance2;
	float lightCoef = 0;

	tuple<float, Object> tupleIntersectObject;
	float intersectLight;
	Object objectIntersect;
	bool canSeeLightSource;
	Vector visibility;

	Vector contribDirect = Vector(0, 0, 0);

	Direction indirectDirection;
	bool sameSide;
	Ray indirectRay;
	Vector radianceContribindirect;
	Vector contribIndirect = Vector(0, 0, 0);
	tuple<Direction, float> indirectDirCoef;
	float coefIndirect = 1;
	float pdf;
	uniform_real_distribution<float> u_distrib(0, 1);
	uniform_real_distribution<float> v_distrib(0, 1);
	float u;
	float v;

	directionToLight = Direction((light.center - x));
	x = x + directionToLight * (float)0.01; // Added an Epsilon for our object not to cast shadow on themselves
	for (int i = 0; i < numberOfRayToLight; i++) {
		r = theta(generator);
		r2 = phi(generator);
		//r = ((float)rand() / (RAND_MAX)) * (float)(2 * M_PI);
		//r2 = ((float)rand() / (RAND_MAX)) * (float)(M_PI);


		randomDirectionToLight = Direction(((Vector(light.center) + Vector({ light.radius * cos(r) * sin(r2) , light.radius * sin(r) * sin(r2), light.radius * cos(r2) })) - x));
		//randomDirectionToLight = Direction(Vector({ light.center.values[0] - r + 1, light.center.values[1] - r2 + 1, light.center.values[2] - r3 + 1 }) - x);


		randomRayOnLight = Ray(x, randomDirectionToLight);

		directionToLightNormalized = Direction(randomRayOnLight.direction.normalize());
		lightDistance2 = randomRayOnLight.direction.dot(randomRayOnLight.direction);
		lightCoef += normal.dot(directionToLightNormalized / (float)(M_PI * lightDistance2)) < 0 ? 0 : normal.dot(directionToLightNormalized / lightDistance2); // distance * Pi

		tupleIntersectObject = rayIntersectObjects(Ray(x, directionToLightNormalized), scene);
		intersectLight = get<0>(tupleIntersectObject);
		objectIntersect = get<1>(tupleIntersectObject);
		canSeeLightSource = (intersectLight == -1 ? true : ((intersectLight * intersectLight) > lightDistance2));
		visibility = canSeeLightSource ? Vector(1, 1, 1) : Vector(0, 0, 0);

		contribDirect = contribDirect + (visibility * lightEmission * lightCoef * albedo);
		///*Vector({visibility.values[0] * lightEmission.values[0] * lightCoef * albedo.values[0],
	//visibility.values[1] * lightEmission.values[1] * lightCoef * albedo.values[1],
	//visibility.values[2] * lightEmission.values[2] * lightCoef * albedo.values[2] });


		u = u_distrib(generator);
		v = v_distrib(generator);

		indirectDirCoef = sample_cosinus(u, v);
		indirectDirection = get<0>(indirectDirCoef);
		indirectDirection = rotate_vector(normal, indirectDirection);

		pdf = get<1>(indirectDirCoef);
		///*sameSide = (normal.dot(indirectDirection) * normal.dot(ray.direction * -1)) > 0;
		//if (!sameSide) {
		//	indirectDirection = Direction((indirectDirection*-1).values);
		//}
		coefIndirect = (indirectDirection.dot(normal) / M_PI) / pdf;

		indirectRay = Ray(x + 0.01 * indirectDirection, indirectDirection);
		radianceContribindirect = radiance(indirectRay, depth + 1, scene);
		if (radianceContribindirect.data[0] == -1) {
			contribIndirect = contribIndirect + Vector(0, 0, 0);
		}
		else {
			contribIndirect = contribIndirect + (radianceContribindirect * albedo);//Vector({ radianceContribindirect.values[0] * albedo.values[0], radianceContribindirect.values[1] * albedo.values[1], radianceContribindirect.values[2] * albedo.values[2] });
		}
	}

	return (contribDirect + (contribIndirect * coefIndirect)) / numberOfRayToLight;
}*/

/*Vector mirror(Ray ray, vector<Object> scene, Point x, Direction normal, tuple<float, Object> intersect, Vector albedo, int depth) {
	Direction reflectedDirection;
	Ray reflectedRay;
	Vector radianceReflectedRayPixel;

	reflectedDirection = reflect(normal, ray.direction);
	reflectedRay = Ray(x + 0.01 * reflectedDirection, reflectedDirection);
	radianceReflectedRayPixel = radiance(reflectedRay, depth + 1, scene);
	if (radianceReflectedRayPixel.data[0] == -1) {
		return Vector(0, 0, 0);
	}
	else {
		return radianceReflectedRayPixel * albedo;
		//Vector({ radianceReflectedRayPixel.values[0] * albedo.values[0], radianceReflectedRayPixel.values[1] * albedo.values[1], radianceReflectedRayPixel.values[2] * albedo.values[2] });
	}
}*/

/*Vector glass(Ray ray, vector<Object> scene, Point x, Direction normal, tuple<float, Object> intersect, Vector albedo, int depth) {
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
		minstd_rand generator(rd());
		uniform_real_distribution<float> distribution(0, 1);
		float r = distribution(generator);

		if (r < coef) {
			transmittedRay = Ray(x + 0.03 * get<1>(transmittedDirection), get<1>(transmittedDirection));
			radianceTransmittedRayPixel = (Vector)radiance(transmittedRay, depth + 1, scene);
			if (radianceTransmittedRayPixel.data[0] == -1) {
				contribRefract = Vector(0, 0, 0);
			}
			else {
				contribRefract = radianceTransmittedRayPixel * albedo;
				//Vector({ radianceTransmittedRayPixel.values[0] * albedo.values[0], radianceTransmittedRayPixel.values[1] * albedo.values[1], radianceTransmittedRayPixel.values[2] * albedo.values[2] });
			}
			return (1 / coef) * contribRefract * coef;
		}
		else {

			contribReflect = mirror(ray, scene, x, normal, intersect, albedo, depth);
			return (1 / (1 - coef)) * contribReflect * (1 - coef);
		}
	}
}*/


/*Vector radiance(Ray ray, int depth, vector<Sphere> scene) {

	float r;
	float coefRR = depth == 0 ? 1 : (float)0.5;
	//random_device rd;
	//default_random_engine generator(rd());
	//uniform_real_distribution<float> urd(0,1);
	//r = urd(generator);
	//srand(time(nullptr));
	r = ((float)rand() / (RAND_MAX));

	if (r > coefRR) {
		return Vector({ 0,0,0 });
	}
	
	if (depth == 5) {
		return Vector({ 0, 0, 0 });
	}
	
	tuple<float,Sphere> intersect = rayIntersectSpheres(ray, scene);
	if (get<0>(intersect) == -1){
		return Vector({ -1,-1,-1 });
	}
	else {
		
		Point x;

		int numberOfRayToLight = 2;
		Sphere light = Sphere(Point({ 125,10,125 }), 24);
		Point lightPosition;
		Vector lightEmission;

		Direction normal;

		Vector albedo;
		
		lightPosition = Point({ 125,10,125 });
		lightEmission = Vector({2000,2000,2000}); //Color and intensity of the lamp

		x = ray.origin + get<0>(intersect) * ray.direction; // Intersection Point

		normal = Direction((x - get<1>(intersect).center).normalize());

		//Sphere color
		albedo = get<1>(intersect).material.material;

		switch (get<1>(intersect).material.materialBehaviour) { //TODO Make function for each case and call it
			case MaterialBehaviour::Diffuse:
				
				return (1/ coefRR) * diffuse(ray, numberOfRayToLight, scene, x, normal, intersect, albedo, light, lightEmission, depth);
				break;

			case MaterialBehaviour::Mirror:

				return (1 / coefRR) * mirror(ray, scene, x, normal, intersect, albedo, depth);
				break; //optional

			case MaterialBehaviour::Glass:

				return (1 / coefRR) * glass(ray, scene, x, normal, intersect, albedo, depth);
				break; //optional

			 // you can have any number of case statements.
			default: //Optional
				cout << "Default for some reason" << endl;
				return Vector({ -1,-1,-1 });
		}
	}
}*/

Point toneMap(Vector v) {
	float data_[3];
	float value;
	for (int i = 0; i < 3; i++) {
		value = floor(powf(v.data[i], (float)1.0 / (float)2.2) * 255); // pow (val, 1/2.2) = correction gamma
		value = value > 255 ? 255 : value;
		value = value < 0 ? 0 : value;
		data_[i] = value;
	}
	return Point(data_);

	//int min = *min_element(v.values.begin(), v.values.end());
	//vector<float> values;
	/*for (auto val : v.values)
	{
		float value = floor(pow(val, 1.0 / 2.2) * 255); // pow (val, 1/2.2) = correction gamma
		value = value > 255 ? 255 : value;
		value = value < 0 ? 0 : value;
		values.push_back(value);
	}
	return Point(values);*/
}

/*float rayIntersectSphere(Ray ray, Sphere sphere) { //Change to return c++2017 optional


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

}*/

/*tuple<float, Sphere> rayIntersectSpheres(Ray ray, vector<Sphere> scene) {
	int numberOfSphere = scene.size();
	vector<tuple<float, Sphere>> intersections(numberOfSphere);
	for (Sphere sphere : scene) {
		intersections.push_back(make_tuple(rayIntersectSphere(ray,sphere),sphere));
	}

	for (int i = 0; i < numberOfSphere; i++) {
		intersections[i] = make_tuple(rayIntersectSphere(ray, scene[i]), scene[i]);
	}

	intersections.erase(remove_if(intersections.begin(), intersections.end(), [](const tuple<float,Sphere>& x) -> bool {return get<0>(x) == -1;}), intersections.end());

	if (intersections.empty()) return make_tuple(-1,Sphere());

	tuple<float, Sphere> intersection = *min_element(intersections.begin(), intersections.end(), [](const tuple<float, Sphere>& x, const tuple<float, Sphere>& y) { return get<0>(x) < get<0>(y);});

	return intersection;


}*/

/*Point rayTrace(int x, int y, vector<Sphere> scene) {
	
	int numberOfRayPerPixel = 5;

	Vector pointNearPlane;
	Vector pointNearPlaneMoved;
	Vector pointFarPlane;

	Direction cameraDirection;

	float fov = (float)1.001;

	pointNearPlane = Vector((float)y,(float)x,0);
	pointNearPlaneMoved = pointNearPlane - Vector(125,125,0); //Move the point on the plane -250:250
	pointFarPlane = Vector(pointNearPlaneMoved.data[0] * fov, pointNearPlaneMoved.data[1] * fov, 1);//Vector({ pointNearPlaneMoved.values[0] * fov,pointNearPlaneMoved.values[1] * fov,1 }); //Apply the fov

	cameraDirection = Direction((pointFarPlane - pointNearPlaneMoved).normalize());

	Ray ray = Ray(Point(pointNearPlane.data), cameraDirection);

	Vector contrib = Vector({0,0,0});
	Vector color;

	for (int i = 0; i < numberOfRayPerPixel; i++) {
		color = radiance(ray, 0, scene);
		if (contrib.data[0] != -1) {
			contrib = contrib + color;
		}
	}
	contrib = contrib / (float)numberOfRayPerPixel;

	return toneMap(contrib);

}*/

/*Vector diffuse(Ray ray, int numberOfRayToLight, vector<Sphere> scene, Point x, Direction normal, tuple<float, Sphere> intersect, Vector albedo, Sphere light, Vector lightEmission, int depth) {
	
	float r;
	float r2;
	Ray randomRayOnLight;
	Direction randomDirectionToLight;
	random_device rd;
	minstd_rand generator(rd());
	uniform_real_distribution<float> theta(0, 2 * M_PI);
	uniform_real_distribution<float> phi(0, M_PI);

	Direction directionToLight;
	Direction directionToLightNormalized;
	float lightDistance2;
	float lightCoef = 0;

	tuple<float, Sphere> tupleIntersectSphere;
	float intersectLight;
	Sphere sphereIntersect;
	bool canSeeLightSource;
	Vector visibility;

	Vector contribDirect = Vector(0,0,0);

	Direction indirectDirection;
	bool sameSide;
	Ray indirectRay;
	Vector radianceContribindirect;
	Vector contribIndirect = Vector(0,0,0);
	tuple<Direction, float> indirectDirCoef;
	float coefIndirect = 1;
	float pdf;
	uniform_real_distribution<float> u_distrib(0, 1);
	uniform_real_distribution<float> v_distrib(0, 1);
	float u;
	float v;
	
	directionToLight = Direction((light.center - x));
	x = x + directionToLight * (float)0.01; // Added an Epsilon for our object not to cast shadow on themselves
	for (int i = 0; i < numberOfRayToLight; i++) {
		r = theta(generator);
		r2 = phi(generator);
		//r = ((float)rand() / (RAND_MAX)) * (float)(2 * M_PI);
		//r2 = ((float)rand() / (RAND_MAX)) * (float)(M_PI);


		randomDirectionToLight = Direction(((Vector(light.center) + Vector({ light.radius * cos(r) * sin(r2) , light.radius * sin(r) * sin(r2), light.radius * cos(r2) })) - x));
		//randomDirectionToLight = Direction(Vector({ light.center.values[0] - r + 1, light.center.values[1] - r2 + 1, light.center.values[2] - r3 + 1 }) - x);


		randomRayOnLight = Ray(x, randomDirectionToLight);

		directionToLightNormalized = Direction(randomRayOnLight.direction.normalize());
		lightDistance2 = randomRayOnLight.direction.dot(randomRayOnLight.direction);
		lightCoef += normal.dot(directionToLightNormalized /(float)(M_PI*lightDistance2)) < 0 ? 0 : normal.dot(directionToLightNormalized / lightDistance2); // distance * Pi

		tupleIntersectSphere = rayIntersectSpheres(Ray(x, directionToLightNormalized), scene);
		intersectLight = get<0>(tupleIntersectSphere);
		sphereIntersect = get<1>(tupleIntersectSphere);
		canSeeLightSource = (intersectLight == -1 ? true : ((intersectLight * intersectLight) > lightDistance2));
		visibility = canSeeLightSource ? Vector(1,1,1) : Vector(0,0,0);

		contribDirect = contribDirect + (visibility * lightEmission * lightCoef * albedo);
		//	Vector({visibility.values[0] * lightEmission.values[0] * lightCoef * albedo.values[0],
		//visibility.values[1] * lightEmission.values[1] * lightCoef * albedo.values[1],
		//visibility.values[2] * lightEmission.values[2] * lightCoef * albedo.values[2] });


		u = u_distrib(generator);
		v = v_distrib(generator);

		indirectDirCoef = sample_cosinus(u,v);
		indirectDirection = get<0>(indirectDirCoef);
		indirectDirection = rotate_vector(normal, indirectDirection);

		pdf = get<1>(indirectDirCoef);
		//sameSide = (normal.dot(indirectDirection) * normal.dot(ray.direction * -1)) > 0;
		//if (!sameSide) {
		//	indirectDirection = Direction((indirectDirection*-1).values);
		//}
		coefIndirect = (indirectDirection.dot(normal) / M_PI) / pdf;

		indirectRay = Ray(x + 0.01 * indirectDirection, indirectDirection);
		radianceContribindirect = radiance(indirectRay, depth + 1, scene);
		if (radianceContribindirect.data[0] == -1) {
			contribIndirect = contribIndirect + Vector(0,0,0);
		}
		else {
			contribIndirect = contribIndirect + (radianceContribindirect * albedo);//Vector({ radianceContribindirect.values[0] * albedo.values[0], radianceContribindirect.values[1] * albedo.values[1], radianceContribindirect.values[2] * albedo.values[2] });
		}
	}

	return (contribDirect + (contribIndirect * coefIndirect)) / numberOfRayToLight;
}*/

/*Vector mirror(Ray ray, vector<Sphere> scene, Point x, Direction normal, tuple<float, Sphere> intersect, Vector albedo, int depth) {

	Direction reflectedDirection;
	Ray reflectedRay;
	Vector radianceReflectedRayPixel;

	reflectedDirection = reflect(normal, ray.direction);
	reflectedRay = Ray(x + 0.01 * reflectedDirection, reflectedDirection);
	radianceReflectedRayPixel = radiance(reflectedRay, depth + 1, scene);
	if (radianceReflectedRayPixel.data[0] == -1) {
		return Vector(0,0,0);
	}
	else {
		return radianceReflectedRayPixel * albedo;
		//Vector({ radianceReflectedRayPixel.values[0] * albedo.values[0], radianceReflectedRayPixel.values[1] * albedo.values[1], radianceReflectedRayPixel.values[2] * albedo.values[2] });
	}
}*/

/*Vector glass(Ray ray, vector<Sphere> scene, Point x, Direction normal, tuple<float, Sphere> intersect, Vector albedo, int depth) {

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
		minstd_rand generator(rd());
		uniform_real_distribution<float> distribution(0, 1);
		float r = distribution(generator);

		if (r < coef) {
			transmittedRay = Ray(x + 0.03 * get<1>(transmittedDirection), get<1>(transmittedDirection));
			radianceTransmittedRayPixel = (Vector)radiance(transmittedRay, depth + 1, scene);
			if (radianceTransmittedRayPixel.data[0] == -1) {
				contribRefract = Vector(0,0,0);
			}
			else {
				contribRefract = radianceTransmittedRayPixel * albedo;
				//Vector({ radianceTransmittedRayPixel.values[0] * albedo.values[0], radianceTransmittedRayPixel.values[1] * albedo.values[1], radianceTransmittedRayPixel.values[2] * albedo.values[2] });
			}
			return (1 / coef) * contribRefract * coef;
		}
		else {

			contribReflect = mirror(ray, scene, x, normal, intersect, albedo, depth);
			return (1 / (1 - coef)) * contribReflect * (1 - coef);
		}
	}
}*/


/*Vector radiance(Ray ray, int depth, vector<Triangle> scene) {

	float r;
	float coefRR = depth == 0 ? 1 : (float)0.5;
	//random_device rd;
	//default_random_engine generator(rd());
	//uniform_real_distribution<float> urd(0,1);
	//r = urd(generator);
	//srand(time(nullptr));
	r = ((float)rand() / (RAND_MAX));

	if (r > coefRR) {
		return Vector({ 0,0,0 });
	}

	if (depth == 5) {
		return Vector({ 0, 0, 0 });
	}

	tuple<float, Triangle> intersect = rayIntersectTriangles(ray, scene);
	if (get<0>(intersect) == -1) {
		return Vector({ -1,-1,-1 });
	}
	else {

		Point x;

		int numberOfRayToLight = 2;
		Sphere light = Sphere(Point({ 125,10,125 }), 24);
		Point lightPosition;
		Vector lightEmission;

		Direction normal;

		Vector albedo;

		lightPosition = Point({ 125,10,125 });
		lightEmission = Vector({ 2000,2000,2000 }); //Color and intensity of the lamp

		x = ray.origin + get<0>(intersect) * ray.direction; // Intersection Point

		normal = get<1>(intersect).normal(x).normalize(); //Direction((x - get<1>(intersect).center).normalize());

		//Sphere color
		albedo = get<1>(intersect).material.material;

		switch (get<1>(intersect).material.materialBehaviour) { //TODO Make function for each case and call it
		case MaterialBehaviour::Diffuse:

			return (1 / coefRR) * diffuse(ray, numberOfRayToLight, scene, x, normal, intersect, albedo, light, lightEmission, depth);
			break;

		case MaterialBehaviour::Mirror:

			return (1 / coefRR) * mirror(ray, scene, x, normal, intersect, albedo, depth);
			break; //optional

		case MaterialBehaviour::Glass:

			return (1 / coefRR) * glass(ray, scene, x, normal, intersect, albedo, depth);
			break; //optional

		 // you can have any number of case statements.
		default: //Optional
			cout << "Default for some reason" << endl;
			return Vector({ -1,-1,-1 });
		}
	}
}

Point rayTrace(int x, int y, vector<Triangle> scene) {

	int numberOfRayPerPixel = 5;

	Vector pointNearPlane;
	Vector pointNearPlaneMoved;
	Vector pointFarPlane;

	Direction cameraDirection;

	float fov = (float)1.001;

	pointNearPlane = Vector((float)y, (float)x, 0);
	pointNearPlaneMoved = pointNearPlane - Vector(125, 125, 0); //Move the point on the plane -250:250
	pointFarPlane = Vector(pointNearPlaneMoved.data[0] * fov, pointNearPlaneMoved.data[1] * fov, 1);//Vector({ pointNearPlaneMoved.values[0] * fov,pointNearPlaneMoved.values[1] * fov,1 }); //Apply the fov

	cameraDirection = Direction((pointFarPlane - pointNearPlaneMoved).normalize());

	Ray ray = Ray(Point(pointNearPlane.data), cameraDirection);

	Vector contrib = Vector({ 0,0,0 });
	Vector color;

	for (int i = 0; i < numberOfRayPerPixel; i++) {
		color = radiance(ray, 0, scene);
		if (contrib.data[0] != -1) {
			contrib = contrib + color;
		}
	}
	contrib = contrib / (float)numberOfRayPerPixel;

	return toneMap(contrib);

}

float rayIntersectTriangle(Ray ray, Triangle triangle) {
	Vector edge1 = triangle.p2 - triangle.p1;
	Vector edge2 = triangle.p3 - triangle.p1;
	Direction h = ray.direction.cross(edge2);
	Vector s = ray.origin - triangle.p1;
	Direction q = s.cross(edge1);
	double a, f, u, v;
	a = edge1.dot(h);
	if (a > -0.01 && a < 0.01)
		return -1; // Le rayon est parall?le au triangle.
	f = 1.0 / a;
	u = f * (s.dot(h));
	if (u < 0.0 || u > 1.0) {
		return -1;
	}
	v = f * ray.direction.dot(q);
	if (v < 0.0 || u + v > 1.0) {
		return -1;
	}
	// On calcule t pour savoir ou le point d'intersection se situe sur la ligne.
	double t = f * edge2.dot(q);
	if (t > 0.01) // // Intersection avec le rayon
		return t;
	else // On a bien une intersection de droite, mais pas de rayon.
		return -1;
}

tuple<float, Triangle> rayIntersectTriangles(Ray ray, vector<Triangle> scene) {
	int numberOfSphere = scene.size();
	vector<tuple<float, Triangle>> intersections(numberOfSphere);

	for (int i = 0; i < numberOfSphere; i++) {
		intersections[i] = make_tuple(rayIntersectTriangle(ray, scene[i]), scene[i]);
	}

	intersections.erase(remove_if(intersections.begin(), intersections.end(), [](const tuple<float, Triangle>& x) -> bool {return get<0>(x) == -1; }), intersections.end());

	if (intersections.empty()) return make_tuple(-1, Triangle());

	tuple<float, Triangle> intersection = *min_element(intersections.begin(), intersections.end(), [](const tuple<float, Triangle>& x, const tuple<float, Triangle>& y) { return get<0>(x) < get<0>(y); });

	return intersection;
}*/

/*Vector diffuse(Ray ray, int numberOfRayToLight, vector<Triangle> scene, Point x, Direction normal, tuple<float, Triangle> intersect, Vector albedo, Sphere light, Vector lightEmission, int depth) {

	float r;
	float r2;
	Ray randomRayOnLight;
	Direction randomDirectionToLight;
	random_device rd;
	minstd_rand generator(rd());
	uniform_real_distribution<float> theta(0, 2 * M_PI);
	uniform_real_distribution<float> phi(0, M_PI);

	Direction directionToLight;
	Direction directionToLightNormalized;
	float lightDistance2;
	float lightCoef = 0;

	tuple<float, Triangle> tupleIntersectSphere;
	float intersectLight;
	Triangle sphereIntersect;
	bool canSeeLightSource;
	Vector visibility;

	Vector contribDirect = Vector(0, 0, 0);

	Direction indirectDirection;
	bool sameSide;
	Ray indirectRay;
	Vector radianceContribindirect;
	Vector contribIndirect = Vector(0, 0, 0);
	tuple<Direction, float> indirectDirCoef;
	float coefIndirect = 1;
	float pdf;
	uniform_real_distribution<float> u_distrib(0, 1);
	uniform_real_distribution<float> v_distrib(0, 1);
	float u;
	float v;

	directionToLight = Direction((light.center - x));
	x = x + directionToLight * (float)0.01; // Added an Epsilon for our object not to cast shadow on themselves
	for (int i = 0; i < numberOfRayToLight; i++) {
		r = theta(generator);
		r2 = phi(generator);
		//r = ((float)rand() / (RAND_MAX)) * (float)(2 * M_PI);
		//r2 = ((float)rand() / (RAND_MAX)) * (float)(M_PI);


		randomDirectionToLight = Direction(((Vector(light.center) + Vector({ light.radius * cos(r) * sin(r2) , light.radius * sin(r) * sin(r2), light.radius * cos(r2) })) - x));
		//randomDirectionToLight = Direction(Vector({ light.center.values[0] - r + 1, light.center.values[1] - r2 + 1, light.center.values[2] - r3 + 1 }) - x);


		randomRayOnLight = Ray(x, randomDirectionToLight);

		directionToLightNormalized = Direction(randomRayOnLight.direction.normalize());
		lightDistance2 = randomRayOnLight.direction.dot(randomRayOnLight.direction);
		lightCoef += normal.dot(directionToLightNormalized / (float)(M_PI * lightDistance2)) < 0 ? 0 : normal.dot(directionToLightNormalized / lightDistance2); // distance * Pi

		tupleIntersectSphere = rayIntersectTriangles(Ray(x, directionToLightNormalized), scene);
		intersectLight = get<0>(tupleIntersectSphere);
		sphereIntersect = get<1>(tupleIntersectSphere);
		canSeeLightSource = (intersectLight == -1 ? true : ((intersectLight * intersectLight) > lightDistance2));
		visibility = canSeeLightSource ? Vector(1, 1, 1) : Vector(0, 0, 0);

		contribDirect = contribDirect + (visibility * lightEmission * lightCoef * albedo);
		//Vector({visibility.values[0] * lightEmission.values[0] * lightCoef * albedo.values[0],
	//visibility.values[1] * lightEmission.values[1] * lightCoef * albedo.values[1],
	//visibility.values[2] * lightEmission.values[2] * lightCoef * albedo.values[2] });


		u = u_distrib(generator);
		v = v_distrib(generator);

		indirectDirCoef = sample_cosinus(u, v);
		indirectDirection = get<0>(indirectDirCoef);
		indirectDirection = rotate_vector(normal, indirectDirection);

		pdf = get<1>(indirectDirCoef);
		//sameSide = (normal.dot(indirectDirection) * normal.dot(ray.direction * -1)) > 0;
		//if (!sameSide) {
		//	indirectDirection = Direction((indirectDirection*-1).values);
		//}
		coefIndirect = (indirectDirection.dot(normal) / M_PI) / pdf;

		indirectRay = Ray(x + 0.01 * indirectDirection, indirectDirection);
		radianceContribindirect = radiance(indirectRay, depth + 1, scene);
		if (radianceContribindirect.data[0] == -1) {
			contribIndirect = contribIndirect + Vector(0, 0, 0);
		}
		else {
			contribIndirect = contribIndirect + (radianceContribindirect * albedo);//Vector({ radianceContribindirect.values[0] * albedo.values[0], radianceContribindirect.values[1] * albedo.values[1], radianceContribindirect.values[2] * albedo.values[2] });
		}
	}

	return (contribDirect + (contribIndirect * coefIndirect)) / numberOfRayToLight;
}

Vector mirror(Ray ray, vector<Triangle> scene, Point x, Direction normal, tuple<float, Triangle> intersect, Vector albedo, int depth) {

	Direction reflectedDirection;
	Ray reflectedRay;
	Vector radianceReflectedRayPixel;

	reflectedDirection = reflect(normal, ray.direction);
	reflectedRay = Ray(x + 0.01 * reflectedDirection, reflectedDirection);
	radianceReflectedRayPixel = radiance(reflectedRay, depth + 1, scene);
	if (radianceReflectedRayPixel.data[0] == -1) {
		return Vector(0, 0, 0);
	}
	else {
		return radianceReflectedRayPixel * albedo;
		//Vector({ radianceReflectedRayPixel.values[0] * albedo.values[0], radianceReflectedRayPixel.values[1] * albedo.values[1], radianceReflectedRayPixel.values[2] * albedo.values[2] });
	}
}

Vector glass(Ray ray, vector<Triangle> scene, Point x, Direction normal, tuple<float, Triangle> intersect, Vector albedo, int depth) {

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
		minstd_rand generator(rd());
		uniform_real_distribution<float> distribution(0, 1);
		float r = distribution(generator);

		if (r < coef) {
			transmittedRay = Ray(x + 0.03 * get<1>(transmittedDirection), get<1>(transmittedDirection));
			radianceTransmittedRayPixel = (Vector)radiance(transmittedRay, depth + 1, scene);
			if (radianceTransmittedRayPixel.data[0] == -1) {
				contribRefract = Vector(0, 0, 0);
			}
			else {
				contribRefract = radianceTransmittedRayPixel * albedo;
				//Vector({ radianceTransmittedRayPixel.values[0] * albedo.values[0], radianceTransmittedRayPixel.values[1] * albedo.values[1], radianceTransmittedRayPixel.values[2] * albedo.values[2] });
			}
			return (1 / coef) * contribRefract * coef;
		}
		else {

			contribReflect = mirror(ray, scene, x, normal, intersect, albedo, depth);
			return (1 / (1 - coef)) * contribReflect * (1 - coef);
		}
	}
}*/

// TOOLS
/*tuple<Direction, float> sample_cosinus(float u, float v) {

	float phi = 2 * M_PI * u;
	float sqrt_v = sqrtf(v);
	float theta = acosf(sqrt_v);
	float sqrt_1_v = sqrtf((1 - v));

	return make_tuple(Direction(cos(phi) * sqrt_1_v, sin(phi) * sqrt_1_v, sqrt_v ), cos(theta) / M_PI);
}

tuple<Direction, Direction> make_base(Direction normal) {

	int sign = (normal.data[2] > 0) - (normal.data[2] < 0);
	float a = -1 / (sign + normal.data[2]);
	float b = normal.data[0] * normal.data[1] * a;

	Direction baseX = Direction( 1 + sign * normal.data[0] * normal.data[0] * a,
									sign * b,
									-sign * normal.data[0] );

	Direction baseY = Direction( b,
									sign + normal.data[1] * normal.data[1] * a,
									- normal.data[1] );

	return make_tuple(baseX, baseY);

}

Direction rotate_vector(Direction normal, Direction indirectDirection) {
	tuple<Direction, Direction> baseXY;
	Direction baseX;
	Direction baseY;

	Direction rotated_vector;

	baseXY = make_base(normal);
	baseX = get<0>(baseXY);
	baseY = get<1>(baseXY);

	rotated_vector = Direction({ (indirectDirection.data[0] * baseX +
						indirectDirection.data[1] * baseY +
						indirectDirection.data[2] * normal) });
	
	return rotated_vector;
}*/






/*int main() {

	vector<Triangle> triangles;
	triangles = parseOffFile("../cube.off");
	cout << "Parse Done" << endl;

	for (int i = 0; i < triangles.size(); i++) {
		cout << "Triangle " << i << endl;
		cout << "{ " << triangles[i].p1.data[0] << ", " << triangles[i].p1.data[1] << ", " << triangles[i].p1.data[2] << "}" << endl;
		cout << "{ " << triangles[i].p2.data[0] << ", " << triangles[i].p2.data[1] << ", " << triangles[i].p2.data[2] << "}" << endl;
		cout << "{ " << triangles[i].p3.data[0] << ", " << triangles[i].p3.data[1] << ", " << triangles[i].p3.data[2] << "}" << endl;
	}

	vector<int> dimensions = { 250,250 };
	vector<vector<vector<int>>> pixels(dimensions[0], vector<vector<int>>(dimensions[1]));

	vector<Object> scene = {																		// Need to be a parameter of radiance
		Sphere(Point({2000 + 250,50,0}),2000, Material(Vector({1,1,0}), MaterialBehaviour::Diffuse)), //Right
		Sphere(Point({-2000,125,0}),2000, Material(Vector({0,1,1}), MaterialBehaviour::Diffuse)), //Left
		Sphere(Point({125,-2000,0}),2000, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse)), //Top
		Sphere(Point({125,2000 + 250,0}),2000, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse)), //Bottom
		Sphere(Point({125,125 ,2000 + 250}),2000, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse)), // Back
		Sphere(Point({125,125 ,-2000}),2000, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse)), // Behind

		Sphere(Point({80,136,136}),32, Material(Vector({1,1,1}), MaterialBehaviour::Mirror)),

		Sphere(Point({156,136,136}),32, Material(Vector({1,1,1}), MaterialBehaviour::Glass, 2.4))
	};

	for (int i = 0; i < triangles.size(); i++) {
		scene.push_back(triangles[i]);
	}

	random_device rd;
	minstd_rand generator(rd());
	uniform_real_distribution<float> distribution(0, 1);
	

	Vector res;
	//std::srand(time(nullptr));
	for (int i = 0; i < dimensions[0]; i++) {
		for (int j = 0; j < dimensions[1]; j++) {

			float dx = distribution(generator);
			float dy = distribution(generator);

			res = rayTrace(i + dx, j + dy, scene);
			vector<float> pixel = { res.data[0], res.data[1], res.data[2] };

			pixels[i][j].insert(pixels[i][j].end(), pixel.begin(), pixel.end());

		}
	}

	cout << "Loop Done" << endl;

	const char* filename = "first_image.ppm";

	createPPMImage(dimensions, pixels, filename);

};*/
