#include "sphere.hpp"
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include "material.hpp"

Sphere::Sphere():
	Shape("Sphere",Material{}),
	center_{0.0,0.0,5.0},
	radius_{1.0}{ std::cout << "Sphere::Constructor" << std::endl; }

Sphere::Sphere(std::string const& name, Material const& material, glm::vec3 const& center, float radius):
	Shape({name},{material}),
	center_{center},
	radius_{radius}{ std::cout << "Sphere::Constructor" << std::endl; }

Sphere::~Sphere(){ std::cout << "Sphere::Destructor" << std::endl; }

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

bool Sphere::intersect (Ray const& ray, float& distance, glm::vec3& intersection) const{
	auto norm_direction = glm::normalize(ray.direction);
	glm::vec3 normal;
	return glm::intersectRaySphere(ray.origin, norm_direction, center_, radius_, intersection, normal);
}