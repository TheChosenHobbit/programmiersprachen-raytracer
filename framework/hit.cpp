#include "hit.hpp"

Hit::Hit():
	is_hit_(false),
	distance_(0.0f),
	intersec_({0.0f, 0.0f, 0.0f}),
	normvec_({0.0f, 0.0f, 0.0f}),
	material_(Material{}),
	type_(""){}

Hit::Hit(bool hit, float distance, glm::vec3 const& intersec, glm::vec3 const& normvec, 
		Material const& material, std::string const& type):
	is_hit_(hit),
	distance_(distance),
	intersec_(intersec),
	normvec_(normvec),
	material_(material),
	type_(type){}