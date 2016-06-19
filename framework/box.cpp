#include "box.hpp"

Box::Box():
	Shape({"Box"},{0,0,0}),
	min_{0,0,0},
	max_{0,0,0}{}

Box::Box(std::string name, Color color, glm::vec3 min, glm::vec3 max):
	Shape({name},{color}),
	min_{min},
	max_{max}{}

float Box::area() const {
	float xLength = abs(max_.x - min_.x);
	float yLength = abs(max_.y - min_.y);
	float zLength = abs(max_.z - min_.z);

	return 2*xLength*yLength + 2*xLength*zLength + 2*yLength*zLength;
}

float Box::volume() const {
	float xLength = abs(max_.x - min_.x);
	float yLength = abs(max_.y - min_.y);
	float zLength = abs(max_.z - min_.z);

	return xLength*yLength*zLength;
}

glm::vec3 Box::getMin() const {
	return min_;
}

glm::vec3 Box::getMax() const {
	return max_;
}

std::ostream& Box::print(std::ostream& os) const{
	Shape::print(os);
	os << "Minimum: " << min_.x << ", " << min_.y << ", " << min_.z << std::endl;
	os << "Maximum: " << max_.x << ", " << max_.y << ", " << max_.z << std::endl;
	return os;
}