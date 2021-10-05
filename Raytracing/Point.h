#ifndef POINT_H
#define POINT_H

#include "Vector.h"
#include "Direction.h"

class Point : public Vector {

public:

	Point();
	//Point(vector<float> values);
	Point(float x, float y, float z);
	Point(float data[3]);

	void operator+(Point p2);
	Direction operator-(Point p2);
	void operator*(float scale);
	void operator/(float divider);

	Point operator+(Direction dir);

};

#endif // !POINT_H