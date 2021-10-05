#ifndef DIRECTION_H
#define DIRECTION_H

#include "Vector.h"

class Direction : public Vector {
public:
	Direction();
	/*Direction(vector<float>);*/
	Direction(float x, float y, float z);
	Direction(float data_[3]);
	Direction(Vector);

	Direction normalize();
	float dot(Direction vec);

	Direction operator+(Direction vec2);
	Direction operator-(Direction vec2);
	Direction operator*(float scale);
	//float operator*(Vector vec);
	Direction operator*(Direction vec);
	Direction operator/(float divider);
};
#endif // !DIRECTION_H