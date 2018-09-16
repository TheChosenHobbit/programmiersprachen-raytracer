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
/*
bool Sphere::intersect (Ray const& ray, float& distance, glm::vec3& intersection, glm::vec3& normal) const{
	auto norm_direction = glm::normalize(ray.direction);
	return glm::intersectRaySphere(ray.origin, norm_direction, center_, radius_, intersection, normal);
}*/
/*
Hit Sphere::intersect (Ray const& ray){
	ray.direction = glm::normalize(ray.direction);
	float distance;
	glm::vec3 intersec, normvec;
	bool hit = glm::intersectRaySphere(ray.origin, ray.direction, center_, radius_ * radius_, distance);

	if(hit){
		intersec = ray.origin + ray.direction * distance;
		normvec = glm::normalize(intersec - center_);
		Hit hi (hit, distance, intersec, normvec, material_, "sphere");

		return hi;
	} else {
		Hit hi{};
		return hi;
	}
}
*/
Hit Sphere::intersect (Ray const& ray){
	ray = ray.transformRay(world_transformation_);
	ray.direction = glm::normalize(ray.direction);
	float distance;
	glm::vec3 world_intersec, world_normvec;
	glm::vec3 local_intersec;
	glm::vec4 local_normvec;
	bool hit = glm::intersectRaySphere(ray.origin, ray.direction, center_, radius_ * radius_, distance);

	if(hit){
		local_intersec = ray.origin + ray.direction * distance;
		local_normvec = glm::vec4{glm::normalize(local_intersec - center_),0.0f};

		world_intersec = glm::vec3{world_transformation_ * glm::vec4{local_intersec,1}};
		world_normvec = glm::vec3{world_transformation_inv_transposed_ * local_normvec};
		Hit hi (hit, distance, world_intersec, world_normvec, material_, "sphere");

		return hi;
	} else {
		Hit hi{};
		return hi;
	}
}