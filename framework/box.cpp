#include "box.hpp"

Box::Box():
	Shape({"Box"},{0,0,0}),
	min_{0,0,0},
	max_{0,0,0}{ std::cout << "Box::Constructor" << std::endl; }

Box::Box(std::string const& name, Color const& color, glm::vec3 const& min, glm::vec3 const& max):
	Shape({name},{color}),
	min_{min},
	max_{max}{ std::cout << "Box::Constructor" << std::endl;}

Box::~Box(){ std::cout << "Box::Destructor" << std::endl; }

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

bool Box::intersect (Ray const& ray, float& t) const{
	return true;
}