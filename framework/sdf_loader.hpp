#ifndef SDF_LOADER_HPP
#define SDF_LOADER_HPP

#include <iostream>
#include <fstream>
#include <glm/vec3.hpp>
#include <map>
#include <sstream>  
#include <string>

#include "box.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "material.hpp"
#include "scene.hpp"
#include "shape.hpp"
#include "sphere.hpp"
#include "light.hpp"

class Sdf_loader
{
	public:
		Sdf_loader();
		Sdf_loader(std::string filename);
		~Sdf_loader();

		Scene load_scene(std::string filename);

	private:
		std::string filename_;
};

#endif // #ifndef SDF_LOADER_HPP