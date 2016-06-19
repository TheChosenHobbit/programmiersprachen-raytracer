#include "sphere.hpp"
#include <cmath>

Sphere::Sphere():
	Shape({"Sphere"},{0.0f,0.0f,0.0f}),
	center_{0,0,0},
	radius_{0}{ std::cout << "Sphere::Constructor" << std::endl; }

Sphere::Sphere(std::string name, Color color, glm::vec3 center, float radius):
	Shape({name},{color}),
	center_{center},
	radius_{radius}{ std::cout << "Sphere::Constructor" << std::endl; }

float Sphere::area() const {
	return 4*M_PI*radius_;
}

float Sphere::volume() const {
	return 4/3*M_PI*radius_*radius_*radius_;
}

glm::vec3 Sphere::getCenter() const {
	return center_;
}

float Sphere::getRadius() const {
	return radius_;
}

std::ostream& Sphere::print(std::ostream& os) const{
	Shape::print(os);
	os << "Center: " << center_.x << ", " << center_.y << ", " << center_.z << std::endl;
	os << "Radius: " << radius_ << std::endl;
	return os;
}