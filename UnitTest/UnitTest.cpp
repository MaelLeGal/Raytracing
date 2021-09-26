#include "pch.h"
#include "CppUnitTest.h"
#include "../Raytracing/Vector.h"
#include "../Raytracing/Vector.cpp"
#include "../Raytracing/Point.h"
#include "../Raytracing/Point.cpp"
#include "../Raytracing/Direction.h"
#include "../Raytracing/Direction.cpp"
#include "../Raytracing/Object.h"
#include "../Raytracing/Object.cpp"
#include "../Raytracing/Sphere.h"
#include "../Raytracing/Sphere.cpp"
#include "../Raytracing/Material.h"
#include "../Raytracing/Material.cpp"
#include "../Raytracing/CreationImagePPM.h"
#include "../Raytracing/CreationImagePPM.cpp"
#include "../Raytracing/Ray.h"
#include "../Raytracing/Ray.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(VectorClass)
	{
	public:

		TEST_METHOD(Operator_plus_1)
		{
			Vector vec1 = Vector({ 1,1,1 });
			Vector vec2 = Vector({ 1,1,1 });
			Vector res = vec1 + vec2;

			vector<float> vec3 = { 2,2,2 };

			Assert::AreEqual(res.values[0], vec3[0]);
			Assert::AreEqual(res.values[1], vec3[1]);
			Assert::AreEqual(res.values[2], vec3[2]);
		}

		TEST_METHOD(Operator_plus_2)
		{
			Vector vec1 = Vector({ 1,1,1 });
			Vector vec2 = Vector({ -1,-1,-1 });
			Vector res = vec1 + vec2;

			vector<float> vec3 = { 0,0,0 };

			Assert::AreEqual(res.values[0], vec3[0]);
			Assert::AreEqual(res.values[1], vec3[1]);
			Assert::AreEqual(res.values[2], vec3[2]);
		}

		TEST_METHOD(Operator_plus_3)
		{
			Vector vec1 = Vector({ (float)1.5,(float)2.5,(float)3.3 });
			Vector vec2 = Vector({ (float)2.5,(float)1.3,(float)-3.2 });
			Vector res = vec1 + vec2;

			vector<float> vec3 = { 4, (float)3.8, (float)0.1 };

			Assert::AreEqual(vec3[0], res.values[0]);
			Assert::AreEqual(vec3[1], res.values[1]);
			Assert::AreEqual(vec3[2], res.values[2]);
		}

		TEST_METHOD(Operator_minus_1)
		{
			Vector vec1 = Vector({ (float)1.5,(float)2.5,(float)3.3 });
			Vector vec2 = Vector({ (float)2.5,(float)1.3,(float)-3.2 });
			Vector res = vec1 - vec2;

			vector<float> vec3 = { (float)-1, (float)1.2, (float)6.5 };

			Assert::AreEqual(vec3[0], res.values[0]);
			Assert::AreEqual(vec3[1], res.values[1]);
			Assert::AreEqual(vec3[2], res.values[2]);
		}

		TEST_METHOD(Operator_multiply_1)
		{
			Vector vec = Vector({ (float)1.5,(float)2.4,(float)3.3 });
			float scale = 2;
			Vector res = vec * scale;

			vector<float> vec2 = { (float)3, (float)4.8, (float)6.6 };

			Assert::AreEqual(vec2[0], res.values[0]);
			Assert::AreEqual(vec2[1], res.values[1]);
			Assert::AreEqual(vec2[2], res.values[2]);
		}

		TEST_METHOD(Operator_multiply_2)
		{
			Vector vec = Vector({ (float)1.5,(float)2.4,(float)3.3 });
			float scale = 2;
			Vector res = scale * vec;

			vector<float> vec2 = { (float)3, (float)4.8, (float)6.6 };

			Assert::AreEqual(vec2[0], res.values[0]);
			Assert::AreEqual(vec2[1], res.values[1]);
			Assert::AreEqual(vec2[2], res.values[2]);
		}

		TEST_METHOD(Operator_multiply_3)
		{
			Vector vec = Vector({ (float)1.5,(float)2.4,(float)3.3 });
			float scale = 1.2;
			Vector res = scale * vec;

			vector<float> vec2 = { (float)1.8, (float)2.88, (float)3.96 };

			Assert::AreEqual(vec2[0], res.values[0]);
			Assert::AreEqual(vec2[1], res.values[1]);
			Assert::AreEqual(vec2[2], res.values[2]);
		}

		TEST_METHOD(Operator_multiply_4)
		{
			Vector vec = Vector({ (float)1.5,(float)2.4,(float)3.3 });
			float scale = -2;
			Vector res = vec * scale;

			vector<float> vec2 = { (float)-3, (float)-4.8, (float)-6.6 };

			Assert::AreEqual(vec2[0], res.values[0]);
			Assert::AreEqual(vec2[1], res.values[1]);
			Assert::AreEqual(vec2[2], res.values[2]);
		}

		TEST_METHOD(Operator_divide_1)
		{
			Vector vec = Vector({ (float)1.5,(float)2.4,(float)3.3 });
			float divider = 2;
			Vector res = vec / divider;

			vector<float> vec2 = { (float)0.75, (float)1.2, (float)1.65 };

			Assert::AreEqual(vec2[0], res.values[0]);
			Assert::AreEqual(vec2[1], res.values[1]);
			Assert::AreEqual(vec2[2], res.values[2]);
		}

		TEST_METHOD(Operator_divide_2)
		{
			Vector vec = Vector({ (float)1.5,(float)2.4,(float)3.3 });
			float divider = 1.2;
			Vector res = vec / divider;

			vector<float> vec2 = { (float)1.25, (float)2, (float)2.75 };

			Assert::AreEqual(vec2[0], res.values[0]);
			Assert::AreEqual(vec2[1], res.values[1]);
			Assert::AreEqual(vec2[2], res.values[2]);
		}

		TEST_METHOD(Operator_divide_3)
		{
			Vector vec = Vector({ (float)1.5,(float)2.4,(float)3.3 });
			float divider = -1.2;
			Vector res = vec / divider;

			vector<float> vec2 = { (float)-1.25, (float)-2, (float)-2.75 };

			Assert::AreEqual(vec2[0], res.values[0]);
			Assert::AreEqual(vec2[1], res.values[1]);
			Assert::AreEqual(vec2[2], res.values[2]);
		}

		TEST_METHOD(Norm_1)
		{
			Vector vec = Vector({ (float)1.5,(float)2.4,(float)3.3 });
			float res = vec.norm();

			float expected = sqrt(18.9);

			Assert::AreEqual(expected, res);

		}

		TEST_METHOD(Norm_2)
		{
			Vector vec = Vector({ (float)-1.5,(float)-2.4,(float)-3.3 });
			float res = vec.norm();

			float expected = sqrt(18.9);

			Assert::AreEqual(expected, res);

		}

		TEST_METHOD(Sqr_norm_1)
		{
			Vector vec = Vector({ (float)1.5,(float)2.4,(float)3.3 });
			float res = vec.sqr_norm();

			float expected = 18.9;

			Assert::AreEqual(expected, res);

		}

		TEST_METHOD(Sqr_norm_2)
		{
			Vector vec = Vector({ (float)-1.5,(float)-2.4,(float)-3.3 });
			float res = vec.sqr_norm();

			float expected = 18.9;

			Assert::AreEqual(expected, res);

		}

		TEST_METHOD(Normalize_1)
		{
			Vector vec = Vector({ (float)-1.5,(float)-2.4,(float)-3.3 });
			Vector res = vec.normalize();

			vector<float> expected = { (float)(-1.5 / sqrt(18.9)),  (float)(-2.4 / sqrt(18.9)) , (float)(-3.3 / sqrt(18.9)) };

			Assert::AreEqual(expected[0], res.values[0]);
			Assert::AreEqual(expected[1], res.values[1]);
			Assert::AreEqual(expected[2], res.values[2]);

		}

		TEST_METHOD(Dot_1)
		{
			Vector vec1 = Vector({ (float)1.5,(float)2.5,(float)3.3 });
			Vector vec2 = Vector({ (float)2.5,(float)1.3,(float)-3.2 });
			float res = vec1.dot(vec2);

			float expected = -3.56;

			Assert::AreEqual(expected, res);

		}
	};

	TEST_CLASS(PointClass)
	{
	public:

	};

	TEST_CLASS(DirectionClass)
	{
	public:

		TEST_METHOD(Operator_plus_1)
		{
			Direction vec1 = Direction({ 1,1,1 });
			Direction vec2 = Direction({ 1,1,1 });
			Direction res = Direction((vec1 + vec2).values);

			vector<float> vec3 = { 2,2,2 };

			Assert::AreEqual(res.values[0], vec3[0]);
			Assert::AreEqual(res.values[1], vec3[1]);
			Assert::AreEqual(res.values[2], vec3[2]);
		}

		TEST_METHOD(Operator_plus_2)
		{
			Direction vec1 = Direction({ 1,1,1 });
			Direction vec2 = Direction({ -1,-1,-1 });
			Direction res = Direction((vec1 + vec2).values);

			vector<float> vec3 = { 0,0,0 };

			Assert::AreEqual(res.values[0], vec3[0]);
			Assert::AreEqual(res.values[1], vec3[1]);
			Assert::AreEqual(res.values[2], vec3[2]);
		}

		TEST_METHOD(Operator_plus_3)
		{
			Direction vec1 = Direction({ (float)1.5,(float)2.5,(float)3.3 });
			Direction vec2 = Direction({ (float)2.5,(float)1.3,(float)-3.2 });
			Direction res = Direction((vec1 + vec2).values);

			vector<float> vec3 = { 4, (float)3.8, (float)0.1 };

			Assert::AreEqual(vec3[0], res.values[0]);
			Assert::AreEqual(vec3[1], res.values[1]);
			Assert::AreEqual(vec3[2], res.values[2]);
		}

		TEST_METHOD(Operator_minus_1)
		{
			Direction vec1 = Direction({ (float)1.5,(float)2.5,(float)3.3 });
			Direction vec2 = Direction({ (float)2.5,(float)1.3,(float)-3.2 });
			Direction res = Direction((vec1 - vec2).values);

			vector<float> vec3 = { (float)-1, (float)1.2, (float)6.5 };

			Assert::AreEqual(vec3[0], res.values[0]);
			Assert::AreEqual(vec3[1], res.values[1]);
			Assert::AreEqual(vec3[2], res.values[2]);
		}

		TEST_METHOD(Operator_multiply_1)
		{
			Direction vec = Direction({ (float)1.5,(float)2.4,(float)3.3 });
			float scale = 2;
			Direction res = Direction((vec * scale).values);

			vector<float> vec2 = { (float)3, (float)4.8, (float)6.6 };

			Assert::AreEqual(vec2[0], res.values[0]);
			Assert::AreEqual(vec2[1], res.values[1]);
			Assert::AreEqual(vec2[2], res.values[2]);
		}

		TEST_METHOD(Operator_multiply_2)
		{
			Direction vec = Direction({ (float)1.5,(float)2.4,(float)3.3 });
			float scale = 2;
			Direction res = Direction((scale * vec).values);

			vector<float> vec2 = { (float)3, (float)4.8, (float)6.6 };

			Assert::AreEqual(vec2[0], res.values[0]);
			Assert::AreEqual(vec2[1], res.values[1]);
			Assert::AreEqual(vec2[2], res.values[2]);
		}

		TEST_METHOD(Operator_multiply_3)
		{
			Direction vec = Direction({ (float)1.5,(float)2.4,(float)3.3 });
			float scale = 1.2;
			Direction res = Direction((scale * vec).values);

			vector<float> vec2 = { (float)1.8, (float)2.88, (float)3.96 };

			Assert::AreEqual(vec2[0], res.values[0]);
			Assert::AreEqual(vec2[1], res.values[1]);
			Assert::AreEqual(vec2[2], res.values[2]);
		}

		TEST_METHOD(Operator_multiply_4)
		{
			Direction vec = Direction({ (float)1.5,(float)2.4,(float)3.3 });
			float scale = -2;
			Direction res = Direction((vec * scale).values);

			vector<float> vec2 = { (float)-3, (float)-4.8, (float)-6.6 };

			Assert::AreEqual(vec2[0], res.values[0]);
			Assert::AreEqual(vec2[1], res.values[1]);
			Assert::AreEqual(vec2[2], res.values[2]);
		}

		TEST_METHOD(Operator_divide_1)
		{
			Direction vec = Direction({ (float)1.5,(float)2.4,(float)3.3 });
			float divider = 2;
			Direction res = Direction((vec / divider).values);

			vector<float> vec2 = { (float)0.75, (float)1.2, (float)1.65 };

			Assert::AreEqual(vec2[0], res.values[0]);
			Assert::AreEqual(vec2[1], res.values[1]);
			Assert::AreEqual(vec2[2], res.values[2]);
		}

		TEST_METHOD(Operator_divide_2)
		{
			Direction vec = Direction({ (float)1.5,(float)2.4,(float)3.3 });
			float divider = 1.2;
			Direction res = Direction((vec / divider).values);

			vector<float> vec2 = { (float)1.25, (float)2, (float)2.75 };

			Assert::AreEqual(vec2[0], res.values[0]);
			Assert::AreEqual(vec2[1], res.values[1]);
			Assert::AreEqual(vec2[2], res.values[2]);
		}

		TEST_METHOD(Operator_divide_3)
		{
			Direction vec = Direction({ (float)1.5,(float)2.4,(float)3.3 });
			float divider = -1.2;
			Direction res = Direction((vec / divider).values);

			vector<float> vec2 = { (float)-1.25, (float)-2, (float)-2.75 };

			Assert::AreEqual(vec2[0], res.values[0]);
			Assert::AreEqual(vec2[1], res.values[1]);
			Assert::AreEqual(vec2[2], res.values[2]);
		}

		TEST_METHOD(Norm_1)
		{
			Direction vec = Direction({ (float)1.5,(float)2.4,(float)3.3 });
			float res = vec.norm();

			float expected = sqrt(18.9);

			Assert::AreEqual(expected, res);

		}

		TEST_METHOD(Norm_2)
		{
			Direction vec = Direction({ (float)-1.5,(float)-2.4,(float)-3.3 });
			float res = vec.norm();

			float expected = sqrt(18.9);

			Assert::AreEqual(expected, res);

		}

		TEST_METHOD(Sqr_norm_1)
		{
			Direction vec = Direction({ (float)1.5,(float)2.4,(float)3.3 });
			float res = vec.sqr_norm();

			float expected = 18.9;

			Assert::AreEqual(expected, res);

		}

		TEST_METHOD(Sqr_norm_2)
		{
			Direction vec = Direction({ (float)-1.5,(float)-2.4,(float)-3.3 });
			float res = vec.sqr_norm();

			float expected = 18.9;

			Assert::AreEqual(expected, res);

		}

		TEST_METHOD(Normalize_1)
		{
			Direction vec = Direction({ (float)-1.5,(float)-2.4,(float)-3.3 });
			Direction res = Direction(vec.normalize().values);

			vector<float> expected = { (float)(-1.5 / sqrt(18.9)),  (float)(-2.4 / sqrt(18.9)) , (float)(-3.3 / sqrt(18.9)) };

			Assert::AreEqual(expected[0], res.values[0]);
			Assert::AreEqual(expected[1], res.values[1]);
			Assert::AreEqual(expected[2], res.values[2]);

		}

		TEST_METHOD(Dot_1)
		{
			Direction vec1 = Direction({ (float)1.5,(float)2.5,(float)3.3 });
			Direction vec2 = Direction({ (float)2.5,(float)1.3,(float)-3.2 });
			float res = vec1.dot(vec2);

			float expected = -3.56;

			Assert::AreEqual(expected, res);

		}

	};

	TEST_CLASS(ObjectClass)
	{
	public:

		TEST_METHOD(Constructor_1)
		{
			Object obj = Object();
			Assert::IsNotNull(&obj);
		}

		TEST_METHOD(Constructor_2)
		{
			Material mat = Material();
			Object obj = Object(mat);
			Assert::IsNotNull(&obj);
			Assert::IsNotNull(&obj.material);
		}

		TEST_METHOD(Constructor_3)
		{
			Material mat = Material(Vector({ 1,1,0 }), MaterialBehaviour::Diffuse);
			Object obj = Object(mat);

			Assert::IsNotNull(&obj);
			Assert::IsNotNull(&obj.material);
			Assert::AreEqual((float)1, obj.material.material.values[0]);
			Assert::AreEqual((float)1, obj.material.material.values[1]);
			Assert::AreEqual((float)0, obj.material.material.values[2]);
			Assert::IsNotNull(&obj.material.materialBehaviour);
			//Assert::AreEqual(obj.material.materialBehaviour, MaterialBehaviour::Diffuse);
		}
	};

	TEST_CLASS(SphereClass)
	{
	public:

		TEST_METHOD(Constructor_1)
		{
			Sphere sph = Sphere();
			Assert::IsNotNull(&sph);
		}

		TEST_METHOD(Constructor_2)
		{
			Point center = Point({ 0,0,0 });
			float radius = 1;
			Sphere sph = Sphere(center, radius);
			Assert::IsNotNull(&sph);
			Assert::AreEqual((float)1, sph.radius);
			Assert::AreEqual((float)0, sph.center.values[0]);
			Assert::AreEqual((float)0, sph.center.values[1]);
			Assert::AreEqual((float)0, sph.center.values[2]);
		}

		TEST_METHOD(Constructor_3)
		{
			Point center = Point({ 0,0,0 });
			float radius = 1;
			Material mat = Material(Vector({ 1,1,0 }), MaterialBehaviour::Diffuse);
			Sphere sph = Sphere(center, radius, mat);
			Assert::IsNotNull(&sph);
			Assert::AreEqual((float)1, sph.radius);
			Assert::AreEqual((float)0, sph.center.values[0]);
			Assert::AreEqual((float)0, sph.center.values[1]);
			Assert::AreEqual((float)0, sph.center.values[2]);
			Assert::IsNotNull(&sph.material);
			Assert::AreEqual((float)1, sph.material.material.values[0]);
			Assert::AreEqual((float)1, sph.material.material.values[1]);
			Assert::AreEqual((float)0, sph.material.material.values[2]);
			Assert::IsNotNull(&sph.material.materialBehaviour);
		}
	};

	TEST_CLASS(RayClass)
	{
	public:

		TEST_METHOD(Constructor_1)
		{
			Ray ray = Ray();
			Assert::IsNotNull(&ray);
		}
		TEST_METHOD(Constructor_2)
		{
			Point origin = Point({ 0,0,0 });
			Direction direction = Direction({ 1,1,1 });
			Ray ray = Ray(origin, direction);
			Assert::IsNotNull(&ray);
			Assert::IsNotNull(&ray.origin);
			Assert::IsNotNull(&ray.direction);
			Assert::AreEqual((float)0, ray.origin.values[0]);
			Assert::AreEqual((float)0, ray.origin.values[1]);
			Assert::AreEqual((float)0, ray.origin.values[2]);
			Assert::AreEqual((float)1, ray.direction.values[0]);
			Assert::AreEqual((float)1, ray.direction.values[1]);
			Assert::AreEqual((float)1, ray.direction.values[2]);
		}

		TEST_METHOD(rayIntersectSphere_1)
		{
			Point origin = Point({ 250,250,0 });
			Direction direction = Direction({ 0,0,1 });
			Ray ray = Ray(origin, direction);

			Point center = Point({ 250,250,300 });
			float radius = 100;
			Sphere sphere = Sphere(center, radius);
			float t0 = rayIntersectSphere(ray, sphere);

			Assert::AreEqual((float)200, t0);
		}

		TEST_METHOD(rayIntersectSphere_2)
		{
			Point origin = Point({ 250,250,0 });
			Direction direction = Direction({ 0,0,1 });
			Ray ray = Ray(origin, direction);

			Point center = Point({ 500,500,300 });
			float radius = 100;
			Sphere sphere = Sphere(center, radius);
			float t0 = rayIntersectSphere(ray, sphere);

			Assert::AreEqual((float)-1, t0);
		}

		TEST_METHOD(rayIntersectSpheres_1)
		{
			Point origin = Point({ 250,250,0 });
			Direction direction = Direction({ 0,0,1 });
			Ray ray = Ray(origin, direction);

			Point center1 = Point({ 250,250,300 });
			float radius1 = 100;
			Sphere sphere1 = Sphere(center1, radius1);

			Point center2 = Point({ 150,250,200 });
			float radius2 = 150;
			Sphere sphere2 = Sphere(center2, radius2);

			vector<Sphere> spheres;
			spheres.push_back(sphere1);
			spheres.push_back(sphere2);

			tuple<float, Sphere> intersect = rayIntersectSpheres(ray, spheres);
			Sphere intersectSphere = get<1>(intersect);
			Assert::AreEqual((float)88.1966, get<0>(intersect));
			Assert::AreEqual((float)150, intersectSphere.radius);
			Assert::AreEqual((float)150, intersectSphere.center.values[0]);
			Assert::AreEqual((float)250, intersectSphere.center.values[1]);
			Assert::AreEqual((float)200, intersectSphere.center.values[2]);
		}

		TEST_METHOD(rayIntersectSpheres_2)
		{
			Point origin = Point({ 250,250,0 });
			Direction direction = Direction({ 0,0,1 });
			Ray ray = Ray(origin, direction);

			Point center1 = Point({ 500,500,300 });
			float radius1 = 100;
			Sphere sphere1 = Sphere(center1, radius1);

			Point center2 = Point({ 0,0,300 });
			float radius2 = 150;
			Sphere sphere2 = Sphere(center2, radius2);

			vector<Sphere> spheres;
			spheres.push_back(sphere1);
			spheres.push_back(sphere2);

			tuple<float, Sphere> intersect = rayIntersectSpheres(ray, spheres);
			Sphere intersectSphere = get<1>(intersect);
			Assert::AreEqual((float)-1, get<0>(intersect));
		}

		TEST_METHOD(Tonemap_1)
		{
			Vector vec = Vector({ 0.8,0.8,0.8 });
			Point p = toneMap(vec);

			Assert::AreEqual((float)230, p.values[0]);
			Assert::AreEqual((float)230, p.values[1]);
			Assert::AreEqual((float)230, p.values[2]);

		}

		TEST_METHOD(Radiance_1)
		{
			vector<Sphere> scene = {																		// Need to be a parameter of radiance
				Sphere(Point({5000 + 500,250,0}),5000, Material(Vector({1,1,0}), MaterialBehaviour::Diffuse)), //Right
				Sphere(Point({-5000,250,0}),5000, Material(Vector({0,1,1}), MaterialBehaviour::Diffuse)), //Left
				Sphere(Point({250,-5000,0}),5000, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse)), //Top
				Sphere(Point({250,5000 + 500,0}),5000, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse)), //Bottom
				Sphere(Point({250,250 ,5000 + 500}),5000, Material(Vector({1,1,1}), MaterialBehaviour::Diffuse)), // Back

				Sphere(Point({150,350,250}),80, Material(Vector({1,1,1}), MaterialBehaviour::Mirror)),

				Sphere(Point({350,350,250}),80, Material(Vector({1,1,1}), MaterialBehaviour::Glass, 1.5))
			};
			
			Point origin = Point({ 250,250,0 });
			Direction direction = Direction({ 0,0,1 });
			Ray ray = Ray(origin, direction);
			Vector pixel = radiance(ray,0, scene);

			Assert::AreEqual((float)0.8, pixel.values[0]);
			Assert::AreEqual((float)0.8, pixel.values[1]);
			Assert::AreEqual((float)0.8, pixel.values[2]);
		}

	};

	TEST_CLASS(CreationImagePPMTest)
	{
	public:

		TEST_METHOD(CreateImagePPM_1)
		{
			vector<int> dimensions = { 3,2 };
			vector<vector<vector<int>>> pixels = { {{255,0,0},{0,255,0},{0,0,255}},
										{{255,255,0},{255,255,255},{0,0,0}} };
			const char* filename = "Unit_test_image.ppm";
			createPPMImage(dimensions, pixels, filename);
		}
	};

	TEST_CLASS(MaterialTest)
	{
	public:

		TEST_METHOD(Constructor_1)
		{

		}

		TEST_METHOD(Reflect_1) {

		}
	};
}
