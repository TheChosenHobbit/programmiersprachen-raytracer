#include "camera.hpp"

Camera::Camera(std::string name, float fov_x):
	name_{name},
	fov_x_{fov_x},
	eye_{0.0,0.0,0.0},
	dir_{0.0,0.0,-1},
	up_{0.0,1,0.0},
	distance_(0.0f){}
	
Camera::Camera(std::string name, float fov_x, glm::vec3 const& position,
			   glm::vec3 const& direction, glm::vec3 const& up):
	name_{name},
	fov_x_{fov_x},
	eye_{position},
	dir_{direction},
	up_{up},
	distance_(0.0f){
		float rad = (fov_x_ * M_PI)/360;
		distance_ = 0.5/(std::tan(rad));
	}
		
Camera::Camera():
	name_{""},
	fov_x_{0.0f},
	eye_{0.0,0.0,0.0},
	dir_{0.0,0.0,-1},
	up_{0.0,1,0.0},
	distance_(0.0f){}
	
Camera::~Camera(){}

Ray Camera::createRay(int x, int y, int height, int width){
	glm::vec3 origin {0.0f, 0.0f, 0.0f};
	glm::vec3 direction{float(x) * 1.0 / float(width) - 0.5, float(y) * 1.0 / float(height) - 0.5, 
      -1.0 * (0.5 / tan(fov_x_/2))}; // distance to canvas = 0.5 / tan(angle / 2)
    Ray ray{origin, direction};
	return ray;
}

std::string Camera::get_name() const{
	return name_;
}
float Camera::get_angle() const{
	return fov_x_;
}
glm::vec3 Camera::get_position() const{
	return eye_;
}
glm::vec3 Camera::get_direction() const{
	return dir_;
} 
glm::vec3 Camera::get_up() const{
	return up_;
}
float Camera::get_distance() const{
	return distance_;
}

Camera& Camera::operator= (Camera const& rhs){
	name_ = rhs.get_name();
	fov_x_ = rhs.get_angle();
	eye_ = rhs.get_position(); 
    dir_ = rhs.get_direction();
	up_ = rhs.get_up();
	return *this;
}

std::ostream& operator<<(std::ostream& os, Camera const& c)
  {
    os << "Camera: \n"
       << "Name: " << c.name_ << "\n"
       << "Pos: (" << c.eye_.x << "," << c.eye_.y << "," << c.eye_.z << ")\n"
       << "Dir: (" << c.dir_.x << "," << c.dir_.y << "," << c.dir_.z << ")\n"
       << "Up: (" << c.up_.x << "," << c.up_.y << "," << c.up_.z << ")\n"
       << "Distance: " << c.distance_ <<"\n"
       << "Winkel: "<< c.fov_x_ << "\n\n";
    return os;
  }