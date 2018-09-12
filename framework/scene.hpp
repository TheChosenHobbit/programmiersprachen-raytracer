#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <vector>
#include <map>
#include "material.hpp"
#include "camera.hpp"
#include "light.hpp"
#include <memory>
#include "shape.hpp"


struct Scene
{
	Camera camera;
	std::map<std::string,Material> materials;
	std::vector<Light> lights;
	std::vector<std::shared_ptr<Shape>> shapes_ptr;
	float x_res = 0.0;
	float y_res = 0.0;
	std::string filename;
	Color backgroundcolor {0.0f, 0.7f, 0.5f};
};

#endif //#define SCENE_HPP



/*
class Scene
{
	
public :
		
	Scene(){}
	void readInput(std::string);
	void addMaterial (Material const&);
	//std::vector<Material> getMaterials();
	Camera cam;

private :
	//std::vector<Material> materials_;

};

Material createMaterial(std::ifstream& line){
	std::string name;
	std::string word;
	float r,g,b,m;

	line >> word;
	name = word;

	line >> word;
	r = std::stof(word);
	line >> word;
	g = std::stof(word);
	line >> word;
	b = std::stof(word);
	Color ka {r,g,b};

	line >> word;
	r = std::stof(word);
	line >> word;
	g = std::stof(word);
	line >> word;
	b = std::stof(word);
	Color kd {r,g,b};

	line >> word;
	r = std::stof(word);
	line >> word;
	g = std::stof(word);
	line >> word;
	b = std::stof(word);
	Color ks {r,g,b};

	line >> word;
	m = std::stof(word);

	Material mat {name, ka, kd, ks, m};

	return mat;

}

std::vector<Material> Scene::getMaterials(){
	return materials_;
}

void Scene::addMaterial(Material const& m){
	materials_.push_back(m);
}

Scene readInput(std::string input){
	
	Scene sc;

	std::string word;
	std::ifstream file (input);

	if(file.is_open()){

		while(file >> word){			

			if(word == "define"){

				file >> word;

				if(word == "material"){ sc.addMaterial(createMaterial(file)); }

				else if (word == "shape"){} 

				else if (word == "light"){

				}
			} else if (word == "camera"){

			} else if (word == "render"){}
		}
		file.close();
	}

	return sc;
}
*/
