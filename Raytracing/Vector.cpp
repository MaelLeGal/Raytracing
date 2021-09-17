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
	/*float max = *max_element(this->values.begin(), this->values.end());
	float min = *max_element(this->values.begin(), this->values.end());
	fabs(max) > fabs(min) ? max = max : max = min;
	
	vector<float> values;
	if (max != 0) {
		
		for (auto value : this->values) {
			values.push_back(value / max);
		}
	}
	else {
		for (int i = 0; i < this->values.size(); i++) {
			values.push_back(0);
		}
	}
	return Vector(values);*/
	return Vector();
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

Vector Vector::operator/(float divider) {
	vector<float> values;
	float thisSize = this->values.size();

	for (int i = 0; i < thisSize; i++) {
		values.push_back(this->values[i] / divider);
	}

	return Vector(values);
}

// Can't compile without ?!!
