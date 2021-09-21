#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

class Vector {
public:

	vector<float> values;

	Vector();
	Vector(vector<float> values);

	float norm();
	float sqr_norm();
	Vector normalize();
	float dot(Vector vec);

	Vector operator+(Vector vec2);
	Vector operator-(Vector vec2);
	Vector operator*(float scale);
	Vector operator/(float divider);

	//TODO operator between Direction and Point;
};

Vector operator*(float scale, Vector vec);
#endif // !VECTOR_H