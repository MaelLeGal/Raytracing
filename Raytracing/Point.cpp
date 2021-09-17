#include "pch.h"
#include "Point.h"

Point::Point() {};

Point::Point(vector<float> values) {
	this->values = values;
}

void Point::operator+(Point vec2) {}

Direction Point::operator-(Point vec2) {
	vector<float> values;
	float thisSize = this->values.size();
	float vec2Size = vec2.values.size();

	if (thisSize == vec2Size) {
		for (int i = 0; i < thisSize; i++) {
			values.push_back(this->values[i] - vec2.values[i]);
		}
	}
	else {
		if (thisSize < vec2Size) {
			for (int i = 0; i < thisSize; i++) {
				values.push_back(this->values[i] - vec2.values[i]);
			}
			values.push_back(-vec2.values[vec2Size - 1]);
		}
		else {
			for (int i = 0; i < vec2Size; i++) {
				values.push_back(this->values[i] - vec2.values[i]);
			}
			values.push_back(this->values[thisSize - 1]);
		}
	}

	return Direction(values);
}

void Point::operator*(float scale) {

}

void Point::operator/(float divider) {
}