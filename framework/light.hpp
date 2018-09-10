#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <glm/vec3.hpp>
#include <string>
#include "color.hpp"

class Light{
public:
	Light();
	Light(std::string const& name, glm::vec3 const& pos, Color const& ld, float brightness);
	~Light();
	
	friend std::ostream& operator<<(std::ostream& os, Light const& light);

	std::string get_name() const;
	glm::vec3 get_pos() const;
	Color get_ld() const;
	float get_brightness() const;

private:
	std::string name_;
	glm::vec3 pos_;
	Color ld_;
	float brightness_;

};

#endif //#define LIGHT_HPP