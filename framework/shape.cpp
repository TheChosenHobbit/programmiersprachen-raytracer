#include "shape.hpp"

Shape::Shape():
	name_{"Shape"},
	material_{},
	world_transformation_{glm::mat4 {1.0f}},
	world_transformation_inv_{glm::mat4 {1.0f}}	
	{ std::cout << "Shape::Constructor" << std::endl; }

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
	os << "Name: " << name_ <<"\n"
	 << "Material: " << material_.name_  <<"\n"
	 << "Ka: " << material_.ka_ <<"\n"
	 << "Kd:" << material_.kd_ <<"\n"
	 << "ks" << material_.ks_ << "\n"
	 << "Exponent für spiegelnde Reflexion: " << material_.m_ << "\n\n";
	return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s)
{
	return s.print(os);
}
