#ifndef VECTOR_H
#define VECTOR_H

#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <string>

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
	string ToString();

	Vector operator+(Vector vec2);
	Vector operator-(Vector vec2);
	Vector operator*(float scale);
	float operator*(Vector vec);
	Vector operator/(float divider);

	//TODO operator between Direction and Point;
};

Vector operator*(float scale, Vector vec);
#endif // !VECTOR_H