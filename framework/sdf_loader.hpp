#ifndef BUW_SDF_LOADER_HPP
#define BUW_SDF_LOADER_HPP

#include <iostream>
#include <fstream>
#include <glm/vec3.hpp>
#include <map>
#include <sstream>  
#include <string>

#include "box.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "cone.hpp"
#include "cylinder.hpp"
#include "light_source.hpp"
#include "material.hpp"
#include "renderer_data.hpp"
#include "scene.hpp"
#include "shape.hpp"
#include "sphere.hpp"
#include "triangle.hpp"

using namespace std;

class  sdf_loader
{
public:
	sdf_loader();
	sdf_loader(std::string filename) const;
	~sdf_loader();

	scene load_scene(std::string filename) const;
	std::string get_file() const;

private:
	std::string filename_;
};

#endif // #ifndef BUW_SDF_LOADER_HPP