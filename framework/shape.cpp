#include "shape.hpp"

Shape::Shape():
	name_{"Shape"},
<<<<<<< HEAD
	material_{Material{}}{ std::cout << "Shape::Constructor" << std::endl; }
=======
	material_{""},
	world_transformation_{glm::mat4 {1.0f}},
	world_transformation_inv_{glm::mat4 {1.0f}}{}
>>>>>>> 54e24ca1884c7e5054ced8ad9bcc572637e2aebb

Shape::Shape(std::string const& name, Material const& material):
	name_{name},
	material_{material}{ std::cout << "Shape::Constructor" << std::endl; }

Shape::~Shape(){ std::cout << "Shape::Destructor" << std::endl;  }

std::string const& Shape::getName() const {
	return name_;
}

Material const& Shape::getMaterial() const {
	return material_;
}

std::ostream& Shape::print(std::ostream& os) const{
	os << "Name: " << name_ << std::endl;
	os << "Material: " << material_.name_ << ", " << material_.ka_ << ", " << material_.kd_ 
	<< ", " << material_.ks_ << ", " << material_.m_ << std::endl; 
	return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s)
{
	return s.print(os);
}
