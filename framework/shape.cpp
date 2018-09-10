#include "shape.hpp"
#include "material.hpp"

Shape::Shape():
	name_{"Shape"},
	material_{""},
	world_transformation_{glm::mat4 {1.0f}},
	world_transformation_inv_{glm::mat4 {1.0f}}{}

Shape::Shape(std::string const& name, std::string material):
	name_{name},
	material_{material}{ std::cout << "Shape::Constructor" << std::endl; }

Shape::~Shape(){ std::cout << "Shape::Destructor" << std::endl;  }

std::string const& Shape::getName() const {
	return name_;
}

std::string const& Shape::getMaterial() const {
	return material_;
}

std::ostream& Shape::print(std::ostream& os) const{
	os << "Name: " << name_ << std::endl;
	os << "Material: " << material_ << std::endl; 
	return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s)
{
	return s.print(os);
}
