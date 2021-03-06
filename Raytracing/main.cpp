#include "pch.h"
#include "Main.h"

Vector radiance(Ray ray, int depth, vector<Object*> scene, vector<Box> boxes) {

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

	//cout << "Call to rayIntersect Objects" << endl;
	//cout << "Start ray Intersect Objects" << endl;
	tuple<float, Object*> intersect = rayIntersectObjects(ray, scene, boxes);
	//cout << "End of rayIntersect Objects call" << endl;
	//cout << get<0>(intersect) << endl;
	if (get<0>(intersect) == -1) {
		//cout << "Je passe bien ici 2" << endl;
		return Vector({ 1,0,1 });
	} else {
		//cout << "intersection found" << endl;
		Point x;

		int numberOfRayToLight = 3;
		Sphere light = Sphere(Point({ 125,10,125 }), 24);
		Point lightPosition;
		Vector lightEmission;

		Direction normal;

		Vector albedo;

		lightPosition = Point({ 125,10,125 });
		lightEmission = Vector({ 2000,2000,2000 }); //Color and intensity of the lamp

		x = ray.origin + get<0>(intersect) * ray.direction; // Intersection Point

		normal = Direction(((*get<1>(intersect)).normal(x)).normalize());

		//Sphere color
		albedo = (*get<1>(intersect)).material.material;

		switch ((*get<1>(intersect)).material.materialBehaviour) {
			case MaterialBehaviour::Diffuse:

				return (1 / coefRR) * diffuse(ray, numberOfRayToLight, scene, boxes, x, normal, intersect, albedo, light, lightEmission, depth);
				break;

			case MaterialBehaviour::Mirror:

				return (1 / coefRR) * mirror(ray, scene, boxes, x, normal, intersect, albedo, depth);
				break; //optional

			case MaterialBehaviour::Glass:

				return (1 / coefRR) * glass(ray, scene, boxes, x, normal, intersect, albedo, depth);
				break; //optional

			 // you can have any number of case statements.
			default: //Optional
				cout << "Default for some reason" << endl;
				return Vector({ -1,-1,-1 });
		}
	}
	//return Vector({ -1,-1,-1 });
}

tuple<float, Object*> rayIntersectObjects(Ray ray, vector<Object*> scene, vector<Box> boxes) {
	//int numberOfObject = scene.size();
	//vector<tuple<float, Object*>> intersections(numberOfObject);
	//for (Sphere sphere : scene) {
	//	intersections.push_back(make_tuple(rayIntersectSphere(ray,sphere),sphere));
	//}

	//cout << "Ray intersect boxes" << endl;
	//float testIntersectBox = boxes[0].rayIntersect(ray);
	//cout << "Ray intersect boxes end" << endl;
	//if (testIntersectBox != -1) { cout << "Value intersection with box : " << boxes[0].rayIntersect(ray) << endl; }
	//else { cout << " No intersection with biggest box ?" << endl; }
	tuple<int, int> indexesTriangles = fall_into_boxes(ray, boxes[0], boxes);
	vector<tuple<float, Object*>> intersections; // ((get<1>(indexesTriangles) - get<0>(indexesTriangles)) + 1);
	if (get<0>(indexesTriangles) != -1) {
		//cout << get<0>(indexesTriangles) << " " << get<1>(indexesTriangles) << endl;
		for (int i = get<0>(indexesTriangles); i < get<1>(indexesTriangles); i++) {
			float dist = scene[i]->rayIntersect(ray);
			if (dist != -1) {
				intersections.push_back(make_tuple(dist, scene[i]));
				//cout << get<0>(intersections[i]) << endl;
				//cout << get<0>(intersections.at(intersections.size()-1)) << endl;
			}
		}
	}

	if (intersections.empty()) {
		//cout << "Empty" << endl;
		return make_tuple(-1, new Object());
	}
	//cout << "before min : " << get<0>(intersections.at(0)) << endl;
	tuple<float, Object*> intersection = *min_element(intersections.begin(), intersections.end(), [](const tuple<float, Object*>& x, const tuple<float, Object*>& y) { return get<0>(x) < get<0>(y); });
	//cout << "Inside : " << get<0>(intersection) << endl;

	return intersection;
	/*if (get<0>(indexesTriangles) != -1) {
		//cout << "Inside box" << endl;
		cout << get<0>(indexesTriangles) << " " << get<1>(indexesTriangles) << endl;
		//for (int i = get<0>(indexesTriangles); i < get<1>(indexesTriangles); i++) {
		//	intersections[i] = make_tuple(scene[i]->rayIntersect(ray), scene[i]);
		//}
		//get<0>(indexesTriangles) = 0;
		//get<1>(indexesTriangles) = 997;
		vector<tuple<float, Object*>> intersections((get<1>(indexesTriangles) - get<0>(indexesTriangles))+1);

		for (int i = get<0>(indexesTriangles); i < get<1>(indexesTriangles)+1; i++) {
			// (get<1>(indexesTriangles) == 1995) {
				float dist = scene[i]->rayIntersect(ray);
				if (dist == -1) {
					intersections[i] = make_tuple(-1, new Object());
				}
				else {
					// << dist << endl;
					tuple<float, Object*> tuple = make_tuple(dist, scene[i]);
					//cout << get<0>(tuple) << endl;
					intersections[i] = tuple;
				}
			//}
			//else {
			//	intersections[i] = make_tuple(-1, new Object());
			//}
		}
		cout << "All triangles intersections done" << endl;
		//if (get<1>(indexesTriangles) == 1995) {
			for (int i = 0; i < intersections.size(); i++) {
				//if (get<0>(intersections[i]) != -1) {
				//	cout << get<0>(intersections[i]) << endl;
				//}
				if(get<0>(intersections[i]) == 0){
					get<0>(intersections[i]) = -1;
				}

				//cout << get<0>(intersections[i]) << endl;
			}
		//}

		//cout << intersections.size() << endl;

		intersections.erase(remove_if(intersections.begin(), intersections.end(), [](const tuple<float, Object*>& x) -> bool {return get<0>(x) == -1;}), intersections.end());
		
		//cout << intersections.size() << endl;

		if (intersections.empty()) {
			cout << "Empty !!" << endl;
			return make_tuple(-1, new Object());
		};
		/*cout << intersections.size() << endl;
		cout << "After erase" << endl;
		
		tuple<float, Object*> intersection = *min_element(intersections.begin(), intersections.end(), [](const tuple<float, Object*>& x, const tuple<float, Object*>& y) { return get<0>(x) < get<0>(y);});
		//cout << get<0>(intersection) << endl;
		return intersection;
	}
	else {
		return make_tuple((float) - 1, new Object());
	}*/
	//return make_tuple((float)-1, new Object());
}

Point rayTrace(int x, int y, vector<Object*> scene, vector<Box> boxes) {
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

	//cout << "Number of ray per pixel loop start" << endl;
	for (int i = 0; i < numberOfRayPerPixel; i++) {
		color = radiance(ray, 0, scene, boxes);
		if (contrib.data[0] != -1) {
			contrib = contrib + color;
		}
	}
	contrib = contrib / (float)numberOfRayPerPixel;

	return toneMap(contrib);
}

Vector diffuse(Ray ray, int numberOfRayToLight, vector<Object*> scene, vector<Box> boxes, Point x, Direction normal, tuple<float, Object*> intersect, Vector albedo, Sphere light, Vector lightEmission, int depth) {
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

	tuple<float, Object*> tupleIntersectObject;
	float intersectLight;
	Object* objectIntersect;
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

		tupleIntersectObject = rayIntersectObjects(Ray(x, directionToLightNormalized), scene, boxes);
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
		coefIndirect = (abs(indirectDirection.dot(normal)) / M_PI) / pdf;

		indirectRay = Ray(x + 0.01 * indirectDirection, indirectDirection);
		radianceContribindirect = radiance(indirectRay, depth + 1, scene, boxes);
		if (radianceContribindirect.data[0] == -1) {
			contribIndirect = contribIndirect + Vector(0, 0, 0);
		}
		else {
			contribIndirect = contribIndirect + (radianceContribindirect * albedo);//Vector({ radianceContribindirect.values[0] * albedo.values[0], radianceContribindirect.values[1] * albedo.values[1], radianceContribindirect.values[2] * albedo.values[2] });
		}
	}

	return (contribDirect + (contribIndirect * coefIndirect)) / numberOfRayToLight;
}

Vector mirror(Ray ray, vector<Object*> scene, vector<Box> boxes, Point x, Direction normal, tuple<float, Object*> intersect, Vector albedo, int depth) {
	Direction reflectedDirection;
	Ray reflectedRay;
	Vector radianceReflectedRayPixel;

	reflectedDirection = reflect(normal, ray.direction);
	reflectedRay = Ray(x + 0.01 * reflectedDirection, reflectedDirection);
	radianceReflectedRayPixel = radiance(reflectedRay, depth + 1, scene, boxes);
	if (radianceReflectedRayPixel.data[0] == -1) {
		return Vector(0, 0, 0);
	}
	else {
		return radianceReflectedRayPixel * albedo;
		//Vector({ radianceReflectedRayPixel.values[0] * albedo.values[0], radianceReflectedRayPixel.values[1] * albedo.values[1], radianceReflectedRayPixel.values[2] * albedo.values[2] });
	}
}

Vector glass(Ray ray, vector<Object*> scene, vector<Box> boxes, Point x, Direction normal, tuple<float, Object*> intersect, Vector albedo, int depth) {
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
	transmittedDirection = refract((*get<1>(intersect)).material.indiceOfRefraction, normal, ray.direction, outside);
	coef = get<0>(transmittedDirection);
	if (coef == -1) {
		return mirror(ray, scene, boxes, x, normal, intersect, albedo, depth);
	}
	else {

		random_device rd;
		minstd_rand generator(rd());
		uniform_real_distribution<float> distribution(0, 1);
		float r = distribution(generator);

		if (r < coef) {
			transmittedRay = Ray(x + 0.03 * get<1>(transmittedDirection), get<1>(transmittedDirection));
			radianceTransmittedRayPixel = (Vector)radiance(transmittedRay, depth + 1, scene, boxes);
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

			contribReflect = mirror(ray, scene, boxes, x, normal, intersect, albedo, depth);
			return (1 / (1 - coef)) * contribReflect * (1 - coef);
		}
	}
}

Box createEnglobingBox(vector<Object*> objects) {
	//cout << "At least called" << endl;
	Point maxCoord = Point(numeric_limits<float>::min(), numeric_limits<float>::min(), numeric_limits<float>::min());
	Point minCoord = Point(numeric_limits<float>::max(), numeric_limits<float>::max(), numeric_limits<float>::max());

	Point maxCoordObject;
	Point minCoordObject;

	tuple<Point, Point> coordObject;
	for (int i = 0; i < objects.size(); i++) {
		//cout << "Before call to Englobing cube" << endl;
		coordObject = objects[i]->getEnglobingCube();
		//cout << "After call" << endl;
		maxCoordObject = get<0>(coordObject);
		minCoordObject = get<1>(coordObject);

		//cout << "Max Coord Object : " << maxCoordObject.ToString() << endl;
		//cout << "Min Coord Object : " << minCoordObject.ToString() << endl;

		if (maxCoord.data[0] < maxCoordObject.data[0]) {
			maxCoord.data[0] = maxCoordObject.data[0];
		}

		if (maxCoord.data[1] < maxCoordObject.data[1]) {
			maxCoord.data[1] = maxCoordObject.data[1];
		}

		if (maxCoord.data[2] < maxCoordObject.data[2]) {
			maxCoord.data[2] = maxCoordObject.data[2];
		}

		if (minCoord.data[0] > minCoordObject.data[0]) {
			minCoord.data[0] = minCoordObject.data[0];
		}

		if (minCoord.data[1] > minCoordObject.data[1]) {
			minCoord.data[1] = minCoordObject.data[1];
		}

		if (minCoord.data[2] > minCoordObject.data[2]) {
			minCoord.data[2] = minCoordObject.data[2];
		}
	}

	return Box(maxCoord, minCoord);
}

tuple<vector<Box>, vector<Triangle*>, vector<Object*>> createBoxTree(vector<Box> boxes, Box parentBox, vector<Triangle*> triangles, vector<Object*> scene, int maxDepth, int depth) {

	if (maxDepth == 1) {
		int axis = parentBox.computeBiggestAxis();
		sort(triangles.begin(), triangles.end(), [axis](Triangle* t1, Triangle* t2) {return sort_triangles(t1, t2, axis); });
		sort(scene.begin(), scene.end(), [axis](Object* t1, Object* t2) {return sort_triangles((Triangle*)t1, (Triangle*)t2, axis); });
		parentBox.setTrianglesIndex(0, triangles.size() - 1);
		// Children Box

		// Setting Scene Box children
		parentBox.setChildren(-1, -1);
		boxes[0] = parentBox;
		return make_tuple(boxes, triangles, scene);
	}

	if (depth == maxDepth || (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart) == 1) {
		
		Box childBox1 = createEnglobingBox({ triangles.begin() + parentBox.trianglesIndexStart, triangles.begin() + parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart) / 2 });
		Box childBox2 = createEnglobingBox({ triangles.begin() + parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart) / 2 + 1, triangles.begin() + parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart) });

		int axis = childBox1.computeBiggestAxis();

		sort(triangles.begin() + parentBox.trianglesIndexStart, triangles.begin() + parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart) / 2, [axis](Triangle* t1, Triangle* t2) {return sort_triangles(t1, t2, axis); });
		sort(scene.begin() + parentBox.trianglesIndexStart, scene.begin() + parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart) / 2, [axis](Object* t1, Object* t2) {return sort_triangles((Triangle*)t1, (Triangle*)t2, axis); });
		childBox1.setTrianglesIndex(parentBox.trianglesIndexStart, parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart) / 2);

		axis = childBox2.computeBiggestAxis();

		sort(triangles.begin() + parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart) / 2 + 1, triangles.begin() + parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart), [axis](Triangle* t1, Triangle* t2) {return sort_triangles(t1, t2, axis); });
		sort(scene.begin() + parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart) / 2 + 1, scene.begin() + parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart), [axis](Object* t1, Object* t2) {return sort_triangles((Triangle*)t1, (Triangle*)t2, axis); });
		childBox2.setTrianglesIndex(parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart) / 2 + 1, parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart));

		childBox1.setChildren(-1,-1);
		childBox2.setChildren(-1,-1);

		boxes[parentBox.children[0]] = childBox1;
		boxes[parentBox.children[1]] = childBox2;

		cout << "Child 1 return" << endl;
		cout << childBox1.coordMax.data[0] << " " << childBox1.coordMax.data[1] << " " << childBox1.coordMax.data[2] << endl;
		cout << childBox1.coordMin.data[0] << " " << childBox1.coordMin.data[1] << " " << childBox1.coordMin.data[2] << endl;
		cout << childBox1.trianglesIndexStart << " " << childBox1.trianglesIndexEnd << endl;

		cout << "Child 2 return" << endl;
		cout << childBox2.coordMax.data[0] << " " << childBox2.coordMax.data[1] << " " << childBox2.coordMax.data[2] << endl;
		cout << childBox2.coordMin.data[0] << " " << childBox2.coordMin.data[1] << " " << childBox2.coordMin.data[2] << endl;
		cout << childBox2.trianglesIndexStart << " " << childBox2.trianglesIndexEnd << endl;

		return make_tuple(boxes, triangles, scene);
	}

	if (depth == 1) {
		//Box sceneEnglobingBox = createEnglobingBox(scene);
		int axis = parentBox.computeBiggestAxis();
		sort(triangles.begin(), triangles.end(), [axis](Triangle* t1, Triangle* t2) {return sort_triangles(t1, t2, axis); });
		sort(scene.begin(), scene.end(), [axis](Object* t1, Object* t2) {return sort_triangles((Triangle*)t1, (Triangle*)t2, axis); });
		parentBox.setTrianglesIndex(0, triangles.size() - 1);
		// Children Box

		// Setting Scene Box children
		parentBox.setChildren(1, 2);
		boxes[0] = parentBox;

		return createBoxTree(boxes, parentBox, triangles, scene, maxDepth, depth + 1);
	}
	else {

		Box childBox1 = createEnglobingBox({ triangles.begin() + parentBox.trianglesIndexStart, triangles.begin() + parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart) / 2 });
		Box childBox2 = createEnglobingBox({ triangles.begin() + parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart) / 2 + 1, triangles.begin() + parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart) });

		int axis = childBox1.computeBiggestAxis();

		sort(triangles.begin() + parentBox.trianglesIndexStart, triangles.begin() + parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart) / 2, [axis](Triangle* t1, Triangle* t2) {return sort_triangles(t1, t2, axis); });
		sort(scene.begin() + parentBox.trianglesIndexStart, scene.begin() + parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart) / 2, [axis](Object* t1, Object* t2) {return sort_triangles((Triangle*)t1, (Triangle*)t2, axis); });
		childBox1.setTrianglesIndex(parentBox.trianglesIndexStart, parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart) / 2);

		axis = childBox2.computeBiggestAxis();

		sort(triangles.begin() + parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart) / 2 + 1, triangles.begin() + parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart), [axis](Triangle* t1, Triangle* t2) {return sort_triangles(t1, t2, axis); });
		sort(scene.begin() + parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart) / 2 + 1, scene.begin() + parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart), [axis](Object* t1, Object* t2) {return sort_triangles((Triangle*)t1, (Triangle*)t2, axis); });
		childBox2.setTrianglesIndex(parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart) / 2 + 1, parentBox.trianglesIndexStart + (parentBox.trianglesIndexEnd - parentBox.trianglesIndexStart));

		//childBox1.setChildren(parentBox.children[1]+1, parentBox.children[1] + 2);
		//childBox2.setChildren(childBox1.children[1] + 1, childBox1.children[1] + 2);
		/*if (depth + 1 == maxDepth) {
			childBox1.setChildren(-1,-1);
			childBox2.setChildren(-1,-1);
		}
		else {*/
			childBox1.setChildren(parentBox.children[0] + parentBox.children[1], parentBox.children[0] + parentBox.children[1] + 1);
			childBox2.setChildren(parentBox.children[0] + parentBox.children[1] + 2, parentBox.children[0] + parentBox.children[1] + 3);
		//}
		boxes[parentBox.children[0]] = childBox1;
		boxes[parentBox.children[1]] = childBox2;

		cout << "Child 1" << endl;
		cout << childBox1.coordMax.data[0] << " " << childBox1.coordMax.data[1] << " " << childBox1.coordMax.data[2] << endl;
		cout << childBox1.coordMin.data[0] << " " << childBox1.coordMin.data[1] << " " << childBox1.coordMin.data[2] << endl;
		cout << childBox1.trianglesIndexStart << " " << childBox1.trianglesIndexEnd << endl;

		cout << "Child 2" << endl;
		cout << childBox2.coordMax.data[0] << " " << childBox2.coordMax.data[1] << " " << childBox2.coordMax.data[2] << endl;
		cout << childBox2.coordMin.data[0] << " " << childBox2.coordMin.data[1] << " " << childBox2.coordMin.data[2] << endl;
		cout << childBox2.trianglesIndexStart << " " << childBox2.trianglesIndexEnd << endl;

		tuple<vector<Box>, vector<Triangle*>, vector<Object*>> boxTreeFirstChilds = createBoxTree(boxes, childBox1, triangles, scene, maxDepth, depth + 1);
		return createBoxTree(get<0>(boxTreeFirstChilds), childBox2, get<1>(boxTreeFirstChilds), get<2>(boxTreeFirstChilds), maxDepth, depth + 1);
	}


}

bool sort_triangles(Triangle* t1, Triangle* t2, int axis) {
	return t1->p1.data[axis] < t2->p1.data[axis];
}

tuple<int, int> fall_into_boxes(Ray ray, Box box, vector<Box> boxes) {

	vector<tuple<int, int>> childrenIndexesTriangles;

	//cout << box.rayIntersect(ray) << endl;

	if (box.rayIntersect(ray) != -1) {
		//cout << "Ray intersect" << endl;
		//cout << "Children 1 ray intersect : " << boxes[box.children[0]].rayIntersect(ray) << endl;
		//cout << "Children 2 ray intersect : " << boxes[box.children[1]].rayIntersect(ray) << endl;
		if (box.children[0] != -1 && box.children[1] != -1) {
			//cout << "Children not empty" << endl;
			if (box.children.size() == 1) {
				//cout << "1 children" << endl;
				childrenIndexesTriangles.push_back(fall_into_boxes(ray, boxes[box.children[0]], boxes));
			}
			else {
				//cout << "2 children" << endl;
				//cout << box.children[0] << endl;
				tuple<int, int> children1 = fall_into_boxes(ray, boxes[box.children[0]], boxes);
				//cout << get<0>(children1) << endl;
				//cout << get<1>(children1) << endl;
				if (get<0>(children1) != -1) {
					childrenIndexesTriangles.push_back(children1);
				}
				//cout << "first fall into boxes done" << endl;
				tuple<int, int> children2 = fall_into_boxes(ray, boxes[box.children[1]], boxes);
				//cout << get<0>(children2) << endl;
				//cout << get<1>(children2) << endl;
				if (get<0>(children2) != -1) {
					childrenIndexesTriangles.push_back(children2);
				}//cout << "second fall into boxes done" << endl;
			}
		}
		else {
			//cout << "Return recurs" << endl;
			//cout << box.trianglesIndexStart << " " << box.trianglesIndexEnd << endl;
			return make_tuple(box.trianglesIndexStart, box.trianglesIndexEnd);
		}
	}
	else {
		//cout << "No intersect" << endl;
		return make_tuple(-1, -1);
	}

	if (!childrenIndexesTriangles.empty()) {
		tuple<int, int> indexesTriangles = childrenIndexesTriangles[0]; //TODO select the closest box/triangles
		//cout << get<0>(indexesTriangles) << " " << get<1>(indexesTriangles) << endl;
	
		return indexesTriangles;
	}
	else {
		//cout << "Empty ?!" << endl;
		return make_tuple(-1, -1);
	}
}

tuple<Direction, float> sample_cosinus(float u, float v) {

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
}

int main() {

	vector<Triangle*> triangles;
	float triangleOffset = 50;
	float triangleScale = 10;
	triangles = parseOffFile("../triceratops.off");
	cout << "Parse Done" << endl;

	for (int i = 0; i < triangles.size(); i++) {

		for (int j = 0; j < 3; j++) {
			triangles[i]->p1.data[j] = triangles[i]->p1.data[j] * triangleScale + triangleOffset;
			triangles[i]->p2.data[j] = triangles[i]->p2.data[j] * triangleScale + triangleOffset;
			triangles[i]->p3.data[j] = triangles[i]->p3.data[j] * triangleScale + triangleOffset;
		}

	}

	/*for (int i = 0; i < triangles.size(); i++) {
		cout << "Triangle " << i << endl;
		cout << "{ " << triangles[i]->p1.data[0] << ", " << triangles[i]->p1.data[1] << ", " << triangles[i]->p1.data[2] << "}" << endl;
		cout << "{ " << triangles[i]->p2.data[0] << ", " << triangles[i]->p2.data[1] << ", " << triangles[i]->p2.data[2] << "}" << endl;
		cout << "{ " << triangles[i]->p3.data[0] << ", " << triangles[i]->p3.data[1] << ", " << triangles[i]->p3.data[2] << "}" << endl;
	}*/

	vector<int> dimensions = { 250,250 };
	vector<vector<vector<int>>> pixels(dimensions[0], vector<vector<int>>(dimensions[1]));

	vector<Object*> scene;

	/*vector<Object*> scene = {																		// Need to be a parameter of radiance
		new Sphere(Point({2000 + 250,50,0}),2000, Material(Vector({1,1,0}), MaterialBehaviour::Diffuse)), //Right
		new Sphere(Point({-2000,125,0}),2000, Material(Vector({0,1,1}), MaterialBehaviour::Diffuse)), //Left
		new Sphere(Point({125,-2000,0}),2000, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse)), //Top
		new Sphere(Point({125,2000 + 250,0}),2000, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse)), //Bottom
		new Sphere(Point({125,125 ,2000 + 250}),2000, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse)), // Back
		new Sphere(Point({125,125 ,-2000}),2000, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse)), // Behind

		new Sphere(Point({80,136,136}),32, Material(Vector({1,1,1}), MaterialBehaviour::Mirror)),

		new Sphere(Point({156,136,136}),32, Material(Vector({1,1,1}), MaterialBehaviour::Glass, 2.4))
	};*/

	for (int i = 0; i < triangles.size(); i++) {
		scene.push_back(triangles[i]);
	}

	int maxDepth = 3;
	int size = (int)pow(2, maxDepth) - 1;
	vector<Box> boxes(size);
	// TODO faire une fonction de cr?ation des boites
	cout << "Before Boxes" << endl;

	// Scene Box
	Box sceneEnglobingBox = createEnglobingBox(scene);
	tuple<vector<Box>, vector<Triangle*>, vector<Object*>> boxTree = createBoxTree(boxes, sceneEnglobingBox, triangles, scene, maxDepth, 1);

	boxes = get<0>(boxTree);
	scene = get<2>(boxTree);

	/*for (int i = 0; i < scene.size(); i++) {
		cout << ((Triangle*)scene[i])->p1.ToString() << endl;
	}*/
	cout << "Scene size : " << scene.size() << endl;

	cout << "boxes size : " << boxes.size() << endl;

	

	/*

	cout << "After englobing box" << endl;
	cout << sceneEnglobingBox.coordMax.data[0] << " " << sceneEnglobingBox.coordMax.data[1] << " " << sceneEnglobingBox.coordMax.data[2] << endl;
	cout << sceneEnglobingBox.coordMin.data[0] << " " << sceneEnglobingBox.coordMin.data[1] << " " << sceneEnglobingBox.coordMin.data[2] << endl;
	cout << sceneEnglobingBox.computeBiggestAxis() << endl;
	int axis = sceneEnglobingBox.computeBiggestAxis();

	//cout << triangles[0]->p1.ToString() << endl;
	sort(triangles.begin(), triangles.end(), [axis](Triangle* t1, Triangle* t2){return sort_triangles(t1, t2, axis);}); // Sort triangles
	//cout << triangles[0]->p1.ToString() << endl;
	//cout << ((Triangle*)scene[0])->p1.ToString() << endl;
	sort(scene.begin(), scene.end(), [axis](Object* t1, Object* t2) {return sort_triangles((Triangle*)t1, (Triangle*)t2, axis); }); // Sort triangles
	//cout << ((Triangle*)scene[0])->p1.ToString() << endl;

	for (int i = 0; i < triangles.size(); i++) {
		cout << triangles[i]->p1.data[axis] << endl;
	}

	sceneEnglobingBox.setTrianglesIndex(0, triangles.size()-1);
	// Children Box
	Box childBox1 = createEnglobingBox({triangles.begin() + 0,triangles.begin() + triangles.size() / 2});
	Box childBox2 = createEnglobingBox({ triangles.begin() + triangles.size() / 2, triangles.end()});
	
	// Setting Scene Box children
	//cout << "Before setting children" << endl;
	sceneEnglobingBox.setChildren(1, 2);
	boxes.push_back(sceneEnglobingBox);
	//cout << "After setting children" << endl;

	cout << childBox1.coordMax.data[0] << " " << childBox1.coordMax.data[1] << " " << childBox1.coordMax.data[2] << endl;
	cout << childBox1.coordMin.data[0] << " " << childBox1.coordMin.data[1] << " " << childBox1.coordMin.data[2] << endl;
	axis = childBox1.computeBiggestAxis();
	cout << axis << endl;

	sort(triangles.begin(), triangles.begin() + triangles.size() / 2, [axis](Triangle* t1, Triangle* t2) {return sort_triangles(t1, t2, axis);});
	sort(scene.begin(), scene.begin() + scene.size() / 2, [axis](Object* t1, Object* t2) {return sort_triangles((Triangle*)t1, (Triangle*)t2, axis); });
	childBox1.setTrianglesIndex(sceneEnglobingBox.trianglesIndexStart, (sceneEnglobingBox.trianglesIndexEnd / 2));
	cout << childBox1.trianglesIndexStart << " " << childBox1.trianglesIndexEnd << endl;

	cout << childBox2.coordMax.data[0] << " " << childBox2.coordMax.data[1] << " " << childBox2.coordMax.data[2] << endl;
	cout << childBox2.coordMin.data[0] << " " << childBox2.coordMin.data[1] << " " << childBox2.coordMin.data[2] << endl;
	axis = childBox2.computeBiggestAxis();
	cout << axis << endl;

	sort(triangles.begin() + (sceneEnglobingBox.trianglesIndexEnd/2) + 1, triangles.end(), [axis](Triangle* t1, Triangle* t2) {return sort_triangles(t1, t2, axis);});
	sort(scene.begin() + (sceneEnglobingBox.trianglesIndexEnd/2) + 1, scene.end(), [axis](Object* t1, Object* t2) {return sort_triangles((Triangle*)t1, (Triangle*)t2, axis); });
	childBox2.setTrianglesIndex((sceneEnglobingBox.trianglesIndexEnd/2)+1, sceneEnglobingBox.trianglesIndexEnd);
	cout << childBox2.trianglesIndexStart << " " << childBox2.trianglesIndexEnd << endl;

	Box childBox3 = createEnglobingBox({triangles.begin(),triangles.begin() + childBox1.trianglesIndexStart + (childBox1.trianglesIndexEnd - childBox1.trianglesIndexStart) / 2 });
	Box childBox4 = createEnglobingBox({triangles.begin() + childBox1.trianglesIndexStart + (childBox1.trianglesIndexEnd - childBox1.trianglesIndexStart) / 2 , triangles.begin() + childBox1.trianglesIndexStart + (childBox1.trianglesIndexEnd - childBox1.trianglesIndexStart) });

	childBox1.setChildren(3, 4);
	boxes.push_back(childBox1); //index 1

	axis = childBox3.computeBiggestAxis();
	sort(triangles.begin() + childBox1.trianglesIndexStart, triangles.begin() + childBox1.trianglesIndexStart +(childBox1.trianglesIndexEnd - childBox1.trianglesIndexStart) / 2, [axis](Triangle* t1, Triangle* t2) {return sort_triangles(t1, t2, axis); });
	sort(scene.begin(), scene.begin() + childBox1.trianglesIndexStart + (childBox1.trianglesIndexEnd - childBox1.trianglesIndexStart) / 2, [axis](Object* t1, Object* t2) {return sort_triangles((Triangle*)t1, (Triangle*)t2, axis); });
	childBox3.setTrianglesIndex(childBox1.trianglesIndexStart, (childBox1.trianglesIndexEnd / 2));

	cout << childBox3.trianglesIndexStart << " " << childBox3.trianglesIndexEnd << endl;

	axis = childBox4.computeBiggestAxis();
	sort(triangles.begin() + childBox1.trianglesIndexStart + (childBox1.trianglesIndexEnd - childBox1.trianglesIndexStart) / 2 + 1, triangles.begin() + childBox1.trianglesIndexStart + (childBox1.trianglesIndexEnd - childBox1.trianglesIndexStart), [axis](Triangle* t1, Triangle* t2) {return sort_triangles(t1, t2, axis); });
	sort(scene.begin() + childBox1.trianglesIndexStart + (childBox1.trianglesIndexEnd - childBox1.trianglesIndexStart) / 2 + 1, scene.begin() + childBox1.trianglesIndexStart + (childBox1.trianglesIndexEnd - childBox1.trianglesIndexStart),[axis](Object* t1, Object* t2) {return sort_triangles((Triangle*)t1, (Triangle*)t2, axis); });
	childBox4.setTrianglesIndex(childBox1.trianglesIndexStart + (childBox1.trianglesIndexEnd - childBox1.trianglesIndexStart) / 2 + 1, childBox1.trianglesIndexStart + (childBox1.trianglesIndexEnd - childBox1.trianglesIndexStart));

	cout << childBox4.trianglesIndexStart << " " << childBox4.trianglesIndexEnd << endl;

	cout << childBox2.trianglesIndexStart + (childBox2.trianglesIndexEnd - childBox2.trianglesIndexStart) / 2 << endl;
	Box childBox5 = createEnglobingBox({triangles.begin() + childBox2.trianglesIndexStart, triangles.begin() + childBox2.trianglesIndexStart +(childBox2.trianglesIndexEnd - childBox2.trianglesIndexStart) / 2});
	Box childBox6 = createEnglobingBox({triangles.begin() + childBox2.trianglesIndexStart + (childBox2.trianglesIndexEnd - childBox2.trianglesIndexStart) / 2 , triangles.begin() + childBox2.trianglesIndexEnd });

	childBox2.setChildren(5, 6);
	boxes.push_back(childBox2); //index 2

	axis = childBox5.computeBiggestAxis();
	sort(triangles.begin() + childBox2.trianglesIndexStart, triangles.begin() + childBox2.trianglesIndexStart + (childBox2.trianglesIndexEnd - childBox2.trianglesIndexStart) / 2, [axis](Triangle* t1, Triangle* t2) {return sort_triangles(t1, t2, axis); });
	sort(scene.begin() + childBox2.trianglesIndexStart, scene.begin() + childBox2.trianglesIndexStart + (childBox2.trianglesIndexEnd - childBox2.trianglesIndexStart) / 2, [axis](Object* t1, Object* t2) {return sort_triangles((Triangle*)t1, (Triangle*)t2, axis); });
	childBox5.setTrianglesIndex(childBox2.trianglesIndexStart, childBox2.trianglesIndexStart + (childBox2.trianglesIndexEnd - childBox2.trianglesIndexStart) / 2);

	cout << childBox5.trianglesIndexStart << " " << childBox5.trianglesIndexEnd << endl;

	axis = childBox6.computeBiggestAxis();
	sort(triangles.begin() + childBox2.trianglesIndexStart + (childBox2.trianglesIndexEnd - childBox2.trianglesIndexStart) / 2 + 1, triangles.begin() + childBox2.trianglesIndexEnd, [axis](Triangle* t1, Triangle* t2) {return sort_triangles(t1, t2, axis); });
	sort(scene.begin() + childBox2.trianglesIndexStart + (childBox2.trianglesIndexEnd - childBox2.trianglesIndexStart) / 2 + 1, scene.begin() + childBox2.trianglesIndexEnd, [axis](Object* t1, Object* t2) {return sort_triangles((Triangle*)t1, (Triangle*)t2, axis); });
	childBox6.setTrianglesIndex((childBox2.trianglesIndexEnd / 2) + 1, childBox2.trianglesIndexEnd);

	cout << childBox6.trianglesIndexStart << " " << childBox6.trianglesIndexEnd << endl;

	boxes.push_back(childBox3); //index 3
	boxes.push_back(childBox4); //index 4

	boxes.push_back(childBox5); //index 5
	boxes.push_back(childBox6); //index 6
	*/
	random_device rd;
	minstd_rand generator(rd());
	uniform_real_distribution<float> distribution(0, 1);

	Vector res;

	cout << "Start loop" << endl;
	for (int i = 0; i < dimensions[0]; i++) {
		for (int j = 0; j < dimensions[1]; j++) {

			float dx = distribution(generator);
			float dy = distribution(generator);

			res = rayTrace(i + dx, j + dy, scene, boxes);
			vector<float> pixel = { res.data[0], res.data[1], res.data[2] };

			pixels[i][j].insert(pixels[i][j].end(), pixel.begin(), pixel.end());

		}
	}

	cout << "Loop Done" << endl;

	const char* filename = "first_image.ppm";

	createPPMImage(dimensions, pixels, filename);
};