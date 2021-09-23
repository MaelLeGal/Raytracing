#include "pch.h"
#include "CppUnitTest.h"
#include "../Raytracing/Vector.h"
#include "../Raytracing/Vector.cpp"
#include "../Raytracing/Point.h"
#include "../Raytracing/Point.cpp"
#include "../Raytracing/Direction.h"
#include "../Raytracing/Direction.cpp"

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

			vector<float> expected = { (float)(-1.5/sqrt(18.9)),  (float)(-2.4 / sqrt(18.9)) , (float)(-3.3 / sqrt(18.9)) };

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

		}
	};

	TEST_CLASS(SphereClass)
	{
	public:

		TEST_METHOD(Constructor_1)
		{

		}
	};

	TEST_CLASS(RayClass)
	{
	public:

		TEST_METHOD(Constructor_1)
		{

		}
	};

	TEST_CLASS(CreationImagePPMTests)
	{
	public:

		TEST_METHOD(CreateImagePPM_1)
		{

		}
	};
}
