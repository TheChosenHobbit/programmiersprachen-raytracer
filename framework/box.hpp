#ifndef BOX_HPP
#define BOX_HPP

#include <glm/vec3.hpp>
#include <shape.hpp>
#include "material.hpp"
#include "hit.hpp"

class Box: public Shape
{
  public: 
  	Box();
  	Box(std::string const& name, Material const& material, glm::vec3 const& minimum, glm::vec3 const& maximum);
    Box(std::string const& name, Material const& material, glm::mat4 const& world_transformation, glm::vec3 const& minimum, glm::vec3 const& maximum);

  	~Box();

  	glm::vec3 getMin() const;
  	glm::vec3 getMax() const;

    float area() const override;
    float volume() const override;

    std::ostream& print(std::ostream&) const override;

    //bool intersect (Ray const& ray, float& t, glm::vec3& intersection, glm::vec3& normal) const;
    glm::vec3 generate_normale(glm::vec3 const& v)const;

    Hit intersect(Ray const& ray);


private:
	glm::vec3 min_;
	glm::vec3 max_;

};

#endif //#define BOX_HPP