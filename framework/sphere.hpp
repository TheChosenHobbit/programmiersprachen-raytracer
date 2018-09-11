#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <glm/vec3.hpp>
#include <shape.hpp>
#include "material.hpp"
#include "ray.hpp"

class Sphere: public Shape
{
  public:
  	Sphere();
  	Sphere(std::string const& name, Material const& material, glm::vec3 const& center, float radius);

  	~Sphere();

  	glm::vec3 getCenter() const; //center()
  	float getRadius() const;

    float area () const override;
    float volume() const override;

    std::ostream& print(std::ostream& os) const override;

    bool intersect (Ray const& ray, float& t, glm::vec3& intersection, glm::vec3& normal) const;

private:
	glm::vec3 center_;
	float radius_;
};

#endif //#define SPHERE_HPP