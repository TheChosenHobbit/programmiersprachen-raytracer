#ifndef RAY_HPP
#define RAY_HPP

#include <glm/vec3.hpp>

struct Ray
{
	glm::vec3 origin;
	glm::vec3 direction;

	Ray():
	origin({0.0f, 0.0f, 0.0f}),
	direction({1.0f, 1.0f, 1.0f}){}

	//normalize direction ???
	Ray(glm::vec3 origin, glm::vec3 direction):
	origin(origin),
	direction(direction){}
	
};

#endif