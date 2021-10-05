#include "pch.h"
#include "Direction.h"

Direction::Direction() {};

/*Direction::Direction(vector<float> values) {
	this->values = values;
}*/

Direction::Direction(Vector vec) {
	this->data[0] = vec.data[0];
	this->data[1] = vec.data[1];
	this->data[2] = vec.data[2];
}

Direction::Direction(float x, float y, float z) {
	this->data[0] = x;
	this->data[1] = y;
	this->data[2] = z;
}

Direction::Direction(float data_[3]) {
	this->data[0] = data_[0];
	this->data[1] = data_[1];
	this->data[2] = data_[2];
}

Direction Direction::normalize() {

	float divider = this->norm();
	float data_[3];
	for (int i = 0; i < 3; i++) {
		data_[i] = this->data[i] / divider;
	}
	return Direction(data_);

	/*float thisSize = this->values.size();
	float divider = this->norm();
	vector<float> values(thisSize);
	for (int i = 0; i < thisSize; i++) {
		values[i] = this->values[i] / divider;
	}

	for (auto val : this->values)
	{
		values.push_back(val / divider);
	}

	return Direction(values);*/
}

float Direction::dot(Direction vec) {

	float val = 0;
	for (int i = 0; i < 3; i++) {
		val += this->data[i] * vec.data[i];
	}
	return val;
	
	/*float val = 0;
	if (this->values.size() == vec.values.size()) {
		for (int i = 0; i < this->values.size(); i++) {
			val += this->values[i] * vec.values[i];
		}
	}
	else {
		cout << "The two vectors don't have the same length" << endl;
	}
	return val;*/
}

Direction Direction::operator+(Direction vec2) {

	float data_[3];
	for (int i = 0; i < 3; i++) {
		data_[i] = this->data[i] + vec2.data[i];
	}
	return Direction(data_);

	/*float thisSize = this->values.size();
	float vec2Size = vec2.values.size();
	vector<float> values(thisSize);
	

	if (thisSize == vec2Size) {
		for (int i = 0; i < thisSize; i++) {
			values[i] = this->values[i] + vec2.values[i];
		}
	}
	else {
		cout << "Error, the size of both vectors are not equal" << endl;
		if (thisSize < vec2Size) {
			for (int i = 0; i < thisSize; i++) {
				values.push_back(this->values[i] + vec2.values[i]);
			}
			values.push_back(vec2.values[vec2Size - 1]);
		}
		else {
			for (int i = 0; i < vec2Size; i++) {
				values.push_back(this->values[i] + vec2.values[i]);
			}
			values.push_back(this->values[thisSize - 1]);
		}
	}

	return Direction(values);*/
}

Direction Direction::operator-(Direction vec2) {

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
			//values.push_back(this->values[i] - vec2.values[i]);
			values[i] = this->values[i] - vec2.values[i];
		}
	}
	else {
		cout << "Error both vector do not have the same size" << endl;
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

Direction Direction::operator*(float scale) {

	float data_[3];
	for (int i = 0; i < 3; i++) {
		data_[i] = this->data[i] * scale;
	}
	return Direction(data_);

	/*float thisSize = this->values.size();
	vector<float> values(thisSize);
	

	for (int i = 0; i < thisSize; i++) {
		values[i] = this->values[i] * scale;
	}

	return Direction(values);*/
}

Direction operator*(float scale, Direction vec) {

	float data_[3];
	for (int i = 0; i < 3; i++) {
		data_[i] = vec.data[i] * scale;
	}
	return Direction(data_);

	/*float vecSize = vec.values.size();
	vector<float> values(vecSize);

	for (int i = 0; i < vecSize; i++) {
		values[i] = vec.values[i] * scale;
	}

	return Direction(values);*/
}

/*float Vector::operator*(Vector vec) {

	float value = 0;
	float vecSize = vec.values.size();

	for (int i = 0; i < vecSize; i++) {
		value += this->values[i] * vec.values[i];
	}

	return value;

}*/
Direction Direction::operator*(Direction vec) {

	float data_[3];
	for (int i = 0; i < 3; i++) {
		data_[i] = vec.data[i] * this->data[i];
	}
	return Direction(data_);

	/*float vecSize = vec.values.size();
	vector<float> values(vecSize);

	for (int i = 0; i < vecSize; i++) {
		values[i] = this->values[i] * vec.values[i];
	}

	return Direction(values);*/
}

Direction Direction::operator/(float divider) {

	float data_[3];
	for (int i = 0; i < 3; i++) {
		data_[i] = this->data[i] / divider;
	}
	return Direction(data_);

	/*float thisSize = this->values.size();
	vector<float> values(thisSize);

	for (int i = 0; i < thisSize; i++) {
		values[i] = this->values[i] / divider;
	}

	return Direction(values);*/
}