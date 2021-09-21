#ifndef POINT_H
#define POINT_H

#include "Vector.h"
#include "Direction.h"

class Point : public Vector {

public:

	Point();
	Point(vector<float> values);

	void operator+(Point p2);
	Direction operator-(Point p2);
	void operator*(float scale);
	void operator/(float divider);

};

#endif // !POINT_H