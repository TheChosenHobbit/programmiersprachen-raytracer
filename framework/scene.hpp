#ifndef SCENE_HPP
#define SCENE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "material.hpp"
#include "camera.hpp"

class Scene
{
	
public :
		
	Scene(){}
	/*
	void readInput(std::string);
	void addMaterial (Material const&);
	std::vector<Material> getMaterials();*/
	Camera cam;

private :
	std::vector<Material> materials_;

};
/*
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
#endif