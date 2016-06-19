#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/vec3.hpp>
#include <shape.hpp>
#include "color.hpp"
#include "ray.hpp"

class Sphere: public Shape
{
  public:
  	Sphere();
  	Sphere(std::string name, Color color, glm::vec3 center, float radius);

  	glm::vec3 getCenter() const;
  	float getRadius() const;

    float area () const override;
    float volume() const override;

    std::ostream& print(std::ostream&) const override;

    bool intersect (Ray const&, float&);

private:
	glm::vec3 center_;
	float radius_;
};

#endif //#define SPHERE_HPP