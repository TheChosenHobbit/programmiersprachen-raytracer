#ifndef RAY_HPP
#define RAY_HPP

#include <glm/vec3.hpp>
#include <glm/glm.hpp>

struct Ray
{
	glm::vec3 origin;
	glm::vec3 direction;
	glm::vec3 inv_direction;

	Ray():
	origin({0.0f, 0.0f, 0.0f}),
	direction({1.0f, 1.0f, 1.0f}),
	inv_direction({-1.0f, -1.0f, -1.0f}){}

	Ray(glm::vec3 const& origin, glm::vec3 const& direction):
	origin(origin),
	direction(glm::normalize(direction)),
	inv_direction({1.0/direction.x, 1.0/direction.y, 1.0/direction.z}){}
	
};

#endif