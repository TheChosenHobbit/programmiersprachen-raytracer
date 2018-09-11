#ifndef HIT_HPP
#define HIT_HPP

#include <glm/vec3.hpp>
#include <map>
#include <memory>
#include <vector>
#include "ray.hpp"


struct Hit{

	Hit();
	Hit(bool is_hit, float distance, glm::vec3 const& intersec, glm::vec3 const& normvec);
	
	bool is_hit_;
	float distance_;
	glm::vec3 intersec_;
	glm::vec3 normvec_;
};


#endif