#include "pch.h"
#include "Vector.h"

Vector::Vector() {
};

Vector::Vector(vector<float> values) {
	this->values = values;
}

float Vector::norm() {
	
	float val = 0;
	for (auto value : this->values) {
		val += value * value;
	}
	return sqrt(val);

}

float Vector::sqr_norm() {
	float val = 0;
	for (auto value : this->values) {
		val += value * value;
	}
	return val;
}

Vector Vector::normalize() {

	float divider = this->norm();
	vector<float> values;
	for (auto val : this->values)
	{
		values.push_back(val / divider);
	}

	return Vector(values);
}

float Vector::dot(Vector vec) {

	float val = 0;
	if (this->values.size() == vec.values.size()) {
		for (int i = 0; i < this->values.size(); i++) {
			val += this->values[i] * vec.values[i];
		}
	}
	else {
		cout << "The two vectors don't have the same length" << endl;
	}
	return val;
}

string Vector::ToString() {
	string line = "{";
	for (float val : this->values)
	{
		line += std::to_string(val) + ", ";
	}

	line += "}";

	return line;
}

Vector Vector::operator+(Vector vec2) {
	vector<float> values;
	float thisSize = this->values.size();
	float vec2Size = vec2.values.size();

	if (thisSize == vec2Size) {
		for (int i = 0; i < thisSize; i++) {
			values.push_back(this->values[i] + vec2.values[i]);
		}
	}
	else {
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

	return Vector(values);
}

Vector Vector::operator-(Vector vec2) {
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

	return Vector(values);
}

Vector Vector::operator*(float scale) {
	vector<float> values;
	float thisSize = this->values.size();

	for (int i = 0; i < thisSize; i++) {
		values.push_back(this->values[i] * scale);
	}

	return Vector(values);
}

Vector operator*(float scale, Vector vec) {
	vector<float> values;
	float vecSize = vec.values.size();

	for (int i = 0; i < vecSize; i++) {
		values.push_back(vec.values[i] * scale);
	}

	return Vector(values);
}

Vector Vector::operator/(float divider) {
	vector<float> values;
	float thisSize = this->values.size();

	for (int i = 0; i < thisSize; i++) {
		values.push_back(this->values[i] / divider);
	}

	return Vector(values);
}

// Can't compile without ?!!
