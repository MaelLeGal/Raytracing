#include "Box.h"

Box::Box() {
	this->coordMax = Point(-1,-1,-1);
	this->coordMin = Point(-1, -1, -1);
	this->children[0] = -1;
	this->children[1] = -1;
};

Box::Box(Point coordMax_, Point coordMin_) {
	this->coordMax = coordMax_;
	this->coordMin = coordMin_;
	this->children.push_back(-1);
	this->children.push_back(-1);

	//this->children[0] = -1;
	//this->children[1] = -1;
}

Box::Box(Point coordMax_, Point coordMin_, int children_[2]) {
	this->coordMax = coordMax_;
	this->coordMin = coordMin_;
	this->children.push_back(children_[0]);
	this->children.push_back(children_[1]);
	//this->children[0] = children_[0];
	//this->children[1] = children_[1];
}
float Box::rayIntersect(Ray ray) {

	//cout << "Ray Intersect inside" << endl;

	float minX = (this->coordMin.data[0] - ray.origin.data[0]) / ray.direction.data[0];
	float maxX = (this->coordMax.data[0] - ray.origin.data[0]) / ray.direction.data[0];

	if (minX > maxX) swap(minX, maxX);

	float minY = (this->coordMin.data[1] - ray.origin.data[1]) / ray.direction.data[1];
	float maxY = (this->coordMax.data[1] - ray.origin.data[1]) / ray.direction.data[1];

	if (minY > maxY) swap(minX, maxX);

	if ((minX > maxY) || (minY > maxX)) return -1;

	if (minY > minX) minX = minY;

	if (maxY < maxX) maxX = maxY;

	float minZ = (this->coordMin.data[2] - ray.origin.data[2]) / ray.direction.data[2];
	float maxZ = (this->coordMax.data[2] - ray.origin.data[2]) / ray.direction.data[2];

	if (minZ > maxZ) swap(minZ, maxZ);

	if ((minX > maxZ) || (minZ > maxX)) return -1;

	if (minZ > minX) minX = minZ;

	if (maxZ < maxX) maxX = maxZ;

	return minX;

	//return true;
}


int Box::computeBiggestAxis() {

	float axisX = this->coordMax.data[0] - this->coordMin.data[0];
	float axisY = this->coordMax.data[1] - this->coordMin.data[1];
	float axisZ = this->coordMax.data[2] - this->coordMin.data[2];

	vector<float> axis = { axisX, axisY, axisZ };
	return max_element(axis.begin(), axis.end()) - axis.begin();
}

void Box::setTrianglesIndex(int trianglesIndexStart_, int trianglesIndexEnd_) {
	this->trianglesIndexStart = trianglesIndexStart_;
	this->trianglesIndexEnd = trianglesIndexEnd_;
}
void Box::setChildren(int child1, int child2) {
	this->children[0] = child1;
	this->children[1] = child2;
}