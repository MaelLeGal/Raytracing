#include "pch.h"
#include "Point.h"

Point::Point() {};

/*Point::Point(vector<float> values) {
	this->values = values;
}*/

Point::Point(float x, float y, float z) {
	this->data[0] = x;
	this->data[1] = y;
	this->data[2] = z;
}

Point::Point(float data_[3]) {
	this->data[0] = data_[0];
	this->data[1] = data_[1];
	this->data[2] = data_[2];
}

void Point::operator+(Point vec2) {}

Direction Point::operator-(Point vec2) {

	float data_[3];
	for (int i = 0; i < 3; i++) {
		data_[i] = this->data[i] - vec2.data[i];
	}
	return Direction(data_);

	/*float thisSize = this->values.size();
	float vec2Size = vec2.values.size();
	vector<float> values(thisSize);

	if (thisSize == vec2Size) {
		for (int i = 0; i < thisSize; i++) {
			values[i] = this->values[i] - vec2.values[i];
		}
	}
	else {
		cout << "The size of both vectors are not equal" << endl;
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

	return Direction(values);*/
}

void Point::operator*(float scale) {

}

void Point::operator/(float divider) {
}
Point Point::operator+(Direction dir) {

	float data_[3];
	for (int i = 0; i < 3; i++) {
		data_[i] = this->data[i] + dir.data[i];
	}
	return Point(data_);

	/*float thisSize = this->values.size();
	float dirSize = dir.values.size();
	vector<float> values(thisSize);

	if (thisSize == dirSize) {
		for (int i = 0; i < thisSize; i++) {
			values[i] = this->values[i] + dir.values[i];
		}
	}
	else {
		cout << "Error, the size of both vector are not equal" << endl;
	}
	else {
		if (thisSize < dirSize) {
			for (int i = 0; i < thisSize; i++) {
				values.push_back(this->values[i] + dir.values[i]);
			}
			values.push_back(dir.values[dirSize - 1]);
		}
		else {
			for (int i = 0; i < dirSize; i++) {
				values.push_back(this->values[i] + dir.values[i]);
			}
			values.push_back(this->values[thisSize - 1]);
		}
	}

	return Point(values);*/
}
