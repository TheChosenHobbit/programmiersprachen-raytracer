#ifndef BOX_HPP
#define BOX_HPP

#include <glm/vec3.hpp>
#include <shape.hpp>

class Box: public Shape
{
  public: 
  	Box();
  	Box(glm::vec3 minimum, glm::vec3 maximum);

  	glm::vec3 getMin() const;
  	glm::vec3 getMax() const;

    float area() const override;
    float volume() const override;
private:
	glm::vec3 min_;
	glm::vec3 max_;

};

#endif //#define BOX_HPP