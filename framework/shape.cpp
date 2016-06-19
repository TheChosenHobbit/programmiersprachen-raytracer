#include "shape.hpp"
#include "color.hpp"

Shape::Shape():
	name_{"Shape"},
	color_{0,0,0}{}

Shape::Shape(std::string const& name, Color const& color):
	name_{name},
	color_{color}{}

std::string const& Shape::getName() const {
	return name_;
}

Color const& Shape::getColor() const {
	return color_;
}
