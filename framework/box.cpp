#include "box.hpp"
#include <iostream>
#include <cmath>
#include "material.hpp"
#include "ray.hpp"
#include <catch.hpp>

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

glm::vec3 Box::generate_normale(glm::vec3 const& v)const{
    glm::vec3 normal(0.0,0.0,0.0);

    if (max_.x - v.x > 0){
        normal.x = 1; 
    }
    else if (max_.x - v.x < 0){
        normal.x = -1;
    }

    if (max_.y - v.y > 0){
        normal.y = 1; 
    }
    else if (max_.y - v.y < 0){
        normal.y = -1;
    }

    if (max_.z - v.z > 0){
		normal.z = 1; 
    }
    else if (max_.z - v.z < 0){
        normal.z = -1;
    }

    return normal;
}
/*
bool Box::intersect (Ray const& ray, float& dista, glm::vec3& intersection, glm::vec3& normal) const{
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

	if (min_.x == intersection.x){
        //front: 
        normal = generate_normale(glm::vec3(min_.x, max_.y, max_.z));
    }
    else if (max_.x == intersection.x){
        // back:
        normal = generate_normale(glm::vec3(max_.x, min_.y, min_.z));
    }
    else if (min_.y == intersection.y){
        //left side:
        normal = generate_normale(glm::vec3(max_.x, min_.y, max_.z));
    }
    else if (max_.y == intersection.y){
        //right side:
        normal = generate_normale(glm::vec3(min_.x, max_.y, min_.z) );
    }
    else if (min_.z == intersection.z){
        //bottom: 
        normal = generate_normale(glm::vec3(max_.x, max_.y, min_.z));
    }
    else if (max_.z == intersection.z){
        //top: 
        normal = generate_normale(glm::vec3(min_.x, min_.y, max_.z));
    }
    
    if (tfar > std::max(0.0f, tnear)) {
        dista = sqrt(tnear * tnear * (ray.direction.x * ray.direction.x +
                        ray.direction.y * ray.direction.y + ray.direction.z * 
                        ray.direction.z));
        return true;
    }
	return false;
}
*/

Hit Box::intersect (Ray const& ray){
	float t0, t1;
	float tnear;
	float tfar;
	bool hit = true;
	float distance = -1;
	glm::vec3 normvec;
	glm::vec3 intersec;
	Hit hi{};

	// {0,0,0} abfangen
	if (ray.direction.x == 0 && ray.direction.y == 0 && ray.direction.z == 0) {return hi;}

	if (ray.direction.x == Approx(0.0f))
	{
		
		if(min_.x > ray.origin.x || max_.x < ray.origin.x) {return hi;}
		//find intersect distance with x coord
	} else {

		t0 = (min_.x - ray.origin.x) / ray.direction.x;
		t1 = (max_.x - ray.origin.x) / ray.direction.x;
		tfar = std::max(t0,t1);
		tnear = std::min(t0,t1);

		if (tnear > tfar)
		{
			return hi;
		}
	}

	if (ray.direction.y == Approx(0.0f))
	{
		
		if(min_.y > ray.origin.y || max_.y < ray.origin.y) {return hi;}
		//find intersect distance with y coord
	} else {

		t0 = (min_.y - ray.origin.y) / ray.direction.y;
		t1 = (max_.y - ray.origin.y) / ray.direction.y;

		if(ray.direction.x == Approx(0.0f)){

			tfar = std::max(t0,t1);
			tnear = std::min(t0,t1);

		} else {

			tnear = std::max(tnear, std::min(t0,t1));
			tfar = std::min(tfar, std::max(t0,t1));
		}
		
		if (tnear > tfar)
		{
			return hi;
		}
	}

	if (ray.direction.z == Approx(0.0f))
	{
		
		if(min_.z > ray.origin.z || max_.z < ray.origin.z) {return hi;}
		//find intersect distance with z coord
	} else {

		t0 = (min_.z - ray.origin.z) / ray.direction.z;
		t1 = (max_.z - ray.origin.z) / ray.direction.z;


		if(ray.direction.x == Approx(0.0f) && ray.direction.y == Approx(0.0f)){

			tfar = std::max(t0,t1);
			tnear = std::min(t0,t1);
			
		} else {

			tnear = std::max(tnear, std::min(t0,t1));
			tfar = std::min(tfar, std::max(t0,t1));
		}
		
		if (tnear > tfar)
		{
			return hi;
		}
	}

	if(tnear < 0.0f && tfar < 0.0f) {return hi;} //ray.origin behind box
	else if (tnear < 0.0f && tfar >= 0.0f) {tfar = tnear;} //ray.origin in box
	
	distance = tnear * sqrt(ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y + ray.direction.z * ray.direction.z);
	intersec = ray.origin + ray.direction * tnear; 
	//calc normvector
	if(intersec.x == Approx(min_.x)) 	   {normvec = {-1.0f, 0.0f, 0.0f};}
	else if (intersec.x == Approx(max_.x)) {normvec = {1.0f, 0.0f, 0.0f};}
	else if (intersec.y == Approx(min_.y)) {normvec = {0.0f, -1.0f, 0.0f};}
	else if (intersec.y == Approx(max_.y)) {normvec = {0.0f, 1.0f, 0.0f};}
	else if (intersec.z == Approx(min_.z)) {normvec = {0.0f, 0.0f, -1.0f};}
	else if (intersec.z == Approx(max_.z)) {normvec = {0.0f, 0.0f, 1.0f};}

	//create hit
	hi.is_hit_ = hit;
	hi.distance_ = distance;
	hi.intersec_ = intersec;
	hi.normvec_ = normvec;
	hi.material_ = material_;
	hi.type_ = "box";

	return hi;
}