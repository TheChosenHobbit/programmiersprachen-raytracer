#include "light.hpp"

Light::Light():
	name_{"name"},
	pos_{0.0,0.0,0.0},
	ld_{0.0f, 0.0f, 0.0f},
  brightness_{0.0f}{}

Light::Light(std::string const& name, glm::vec3 const& pos, Color const& ld, float brightness):
	name_{name},
	pos_{pos},
	ld_{ld},
  brightness_{brightness}{}

Light::~Light(){}

  std::string Light::get_name() const
  {
    return name_;
  }

  glm::vec3 Light::get_pos() const
  {
    return pos_;
  }

  Color Light::get_ld() const
  {
    return ld_;
  }
  float Light::get_brightness() const
   {
    return brightness_;
   }

std::ostream& operator<<(std::ostream& os, Light const& light)
  {
    os << "\nLight: " << light.name_ << "\nPosition: (" 
       << light.pos_.x << "," << light.pos_.y << "," << light.pos_.z << ")\n" 
       << "Farbe: " << light.ld_ << "\n\n";
    return os;
  }