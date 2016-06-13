#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/vec3.hpp>
#include <shape.hpp>

class Sphere: public Shape
{
  public:
  	Sphere();
  	Sphere(glm::vec3 center, float radius);

  	glm::vec3 getCenter() const;
  	float getRadius() const;

    float area () const override;
    float volume() const override;
private:
	glm::vec3 center_;
	float radius_;
};

#endif //#define SPHERE_HPP