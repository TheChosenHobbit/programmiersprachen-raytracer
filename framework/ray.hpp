#ifndef RAY_HPP
#define RAY_HPP

#include <glm/vec3.hpp>

struct Ray
{
	glm::vec3 origin;
	glm::vec3 direction;

	Ray():
	origin{glm::vec3{}},
	direction{glm::vec3{}}{}

	Ray(glm::vec3 origin, glm::vec3 direction):
	origin{origin},
	direction{direction}{}

	Ray(Ray const& ray):
	origin{ray.origin},
	direction{ray.direction}{}
};

#endif