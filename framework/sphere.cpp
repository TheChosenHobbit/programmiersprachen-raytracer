#include "sphere.hpp"
#include <cmath>

Sphere::Sphere():
	center_{0,0,0},
	radius_{0}{}

Sphere::Sphere(glm::vec3 center, float radius):
	center_{center},
	radius_{radius}{}

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