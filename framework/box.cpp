#include "box.hpp"
#include <iostream>
#include <cmath>
#include "material.hpp"
#include "ray.hpp"

Box::Box():
	Shape("Box",Material{}),
	min_{0,0,0},
	max_{1,1,1}{ std::cout << "Box::Constructor" << std::endl; }

Box::Box(std::string const& name, Material const& material, glm::vec3 const& min, glm::vec3 const& max):
	Shape({name},{material}),
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

bool Box::intersect (Ray const& ray, float& dista, glm::vec3& intersection) const{
	float tnear,tfar;
	float tnear_x,tnear_y,tnear_z;
	float t0, t1, t_final;
	dista = -1;

	if (ray.direction.x != 0.0)
	{
		t0 = (min_.x - ray.origin.x) / ray.direction.x; // t zu unten links
		t1 = (max_.x - ray.origin.x) / ray.direction.x; // t zu unten rechts
		tnear_x = std::min(t0, t1); //näheres t der x-Achse
		tnear = std::min(t0,t1); // t zum minimum
		tfar = std::max(t0,t1); // t zum maximum
	}
	else 
	{
		if(min_.x > ray.origin.x || max_.x < ray.origin.x) {
			return false;
		}
	}

	if (ray.direction.y != 0.0)
	{
		t0 = (min_.y - ray.origin.y) / ray.direction.y;
		t1 = (max_.y - ray.origin.y) / ray.direction.y;
		tnear_y = std::min(t0, t1);
		tnear = std::max(tnear, std::min(t0,t1)); // näheres t zu einem minimum
		tfar = std::min(tfar, std::max(t0,t1)); // näheres t zu einem maximum
		if (tnear > tfar)
		{
			return false;
		}
	}
	else 
	{
		if(min_.y > ray.origin.y || max_.y < ray.origin.y) {
			return false;
		}
	}

	if (ray.direction.z != 0.0) //einzelne Abfragen?
	{
		t0 = (min_.z - ray.origin.z) / ray.direction.z;
		t1 = (max_.z - ray.origin.z) / ray.direction.z;
		tnear_z = std::min(t0, t1);
		tnear = std::max(tnear, std::min(t0,t1));
		tfar = std::min(tfar, std::max(t0,t1)); 
	}
	else 
	{
		if(min_.z > ray.origin.z || max_.z < ray.origin.z) {return false;}
	}

	if (tnear < 0){

		if(tfar < 0){

			return false;

		}

		t_final = tfar;

	}
	else{
		t_final = tnear;
	}

	intersection = ray.origin + ray.direction * t_final;

	return true;
}