#include "pch.h"
#include "Vector.h"

Vector::Vector() {
};

Vector::Vector(float x, float y, float z) {
	//this->values = values;
	this->data[0] = x;
	this->data[1] = y;
	this->data[2] = z;
}

Vector::Vector(float data_[3]) {
	//this->values = values;
	//cout << this->data[0] << endl;
	/*cout << "Start constructor vector" << endl;
	cout << data_[0] << endl;
	cout << data_[1] << endl;
	cout << data_[2] << endl;*/
	//this->data = data_;
	this->data[0] = data_[0];
	this->data[1] = data_[1];
	this->data[2] = data_[2];

	/*cout << this->data[0] << endl;
	cout << this->data[1] << endl;
	cout << this->data[2] << endl;
	cout << "End constructor vector" << endl;*/
}

float Vector::norm() {
	
	/*float val = 0;
	for (int i = 0; i < 3; i++) {
		val += this->data[i] * this->data[i];
	}*/

	/*for (auto value : this->values) {
		val += value * value;
	}*/

	return sqrt(sqr_norm());

}

float Vector::sqr_norm() {
	float val = 0;
	for (int i = 0; i < 3; i++) {
		val += data[i] * data[i];
	}

	/*for (auto value : this->values) {
		val += value * value;
	}*/
	return val;
}

Vector Vector::normalize() {

	float data_[3];
	float divider = this->norm();
	for (int i = 0; i < 3; i++) {
		data_[i] = this->data[i] / divider;
	}
	return Vector(data_); // TODO maybe no return or return this normalized;

	/*vector<float> values;
	for (auto val : this->values)
	{
		values.push_back(val / divider);
	}

	return Vector(values);*/
}

float Vector::dot(Vector vec) {

	float val = 0;
	for (int i = 0; i < 3; i++) {
		val += this->data[i] * vec.data[i];
	}

	/*if (this->values.size() == vec.values.size()) {
		for (int i = 0; i < this->values.size(); i++) {
			val += this->values[i] * vec.values[i];
		}
	}
	else {
		cout << "The two vectors don't have the same length" << endl;
	}*/
	return val;
}

Vector Vector::cross(Vector vec) {

	float data_[3];

	data_[0] = (this->data[1] * vec.data[3]) - (this->data[3] * vec.data[1]);
	data_[1] = (this->data[3] * vec.data[1]) - (this->data[1] * vec.data[3]);
	data_[2] = (this->data[1] * vec.data[2]) - (this->data[2] * vec.data[1]);

	return Vector(data_);
}

string Vector::ToString() {
	string line = "{";

	for (int i = 0; i < 3; i++) {
		line += to_string(data[i]) + ", ";
	}
	/*for (float val : this->values)
	{
		line += std::to_string(val) + ", ";
	}*/

	line += "}";

	return line;
}

Vector Vector::operator+(Vector vec2) {

	float data_[3];
	for(int i = 0; i < 3; i++){
		data_[i] = this->data[i] + vec2.data[i];
	}
	return Vector(data_);

	/*float thisSize = this->values.size();
	float vec2Size = vec2.values.size();
	vector<float> values(thisSize);
	
	if (thisSize == vec2Size) {
		for (int i = 0; i < thisSize; i++) {
			values[i] = this->values[i] + vec2.values[i];
		}
	}
	else {
		cout << "Error, the two vectors do not have the same size" << endl;
	}*/
	/*else {
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

	return Vector(values);*/
}

Vector Vector::operator-(Vector vec2) {

	float data_[3];
	for (int i = 0; i < 3; i++) {
		data_[i] = this->data[i] - vec2.data[i];
	}
	return Vector(data_);

	/*vector<float> values;
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

	return Vector(values);*/
}

Vector Vector::operator*(float scale) {

	float data_[3];
	for (int i = 0; i < 3; i++) {
		data_[i] = this->data[i] * scale;
	}
	return Vector(data_);

	/*float thisSize = this->values.size();
	vector<float> values(thisSize);
	
	for (int i = 0; i < thisSize; i++) {
		values[i] = this->values[i] * scale;
	}

	return Vector(values);*/
}

Vector operator*(float scale, Vector vec) {

	float data_[3];
	for (int i = 0; i < 3; i++) {
		data_[i] = vec.data[i] * scale;
	}
	return Vector(data_);

	/*float vecSize = vec.values.size();
	vector<float> values(vecSize);

	for (int i = 0; i < vecSize; i++) {
		values[i]  = vec.values[i] * scale;
	}

	return Vector(values);*/
}

/*float Vector::operator*(Vector vec) {

	float value = 0;
	float vecSize = vec.values.size();

	for (int i = 0; i < vecSize; i++) {
		value += this->values[i] * vec.values[i];
	}

	return value;

}*/
Vector Vector::operator*(Vector vec) {

	float data_[3];
	for (int i = 0; i < 3; i++) {
		data_[i] = this->data[i] * vec.data[i];
	}
	return Vector(data_);
	
	/*vector<float> values;
	float vecSize = vec.values.size();

	for (int i = 0; i < vecSize; i++) {
		values.push_back(this->values[i] * vec.values[i]);
	}

	return Vector(values);*/
}

Vector Vector::operator/(float divider) {
	float data_[3];
	for (int i = 0; i < 3; i++) {
		data_[i] = this->data[i] / divider;
	}
	return Vector(data_);

	/*vector<float> values;
	float thisSize = this->values.size();

	for (int i = 0; i < thisSize; i++) {
		values.push_back(this->values[i] / divider);
	}

	return Vector(values);*/
}

// Can't compile without ?!!
