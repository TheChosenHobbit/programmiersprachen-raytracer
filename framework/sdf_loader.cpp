#include "sdf_loader.hpp"

using namespace std;

sdf_loader::sdf_loader(std::string filename):
	filename_{filename}{}

sdf_loader::sdf_loader()
:	filename_{""}{}

sdf_loader::~sdf_loader(){
}
Scene sdf_loader::load_scene(std::string filename) const {
	ifstream file(filename, ios::in);
	Scene s{};
	std::string word = " ";
	std::string name = " ";
	std::stringstream s_stream;
	//std::map<std::string, std::shared_ptr<Shape>> shape_map;


	if(file.good()){
		while(file >> word){  //iteriert über die mit Leerzeichen getrennten "Wörter" im file
			if(word == "#") { // ignoriert Kommentare und geht zum nächsten
				file >> word;
				std::cout << "testing" << std::endl;
			}

			//Camera
			else if(word == "camera"){
				file >> name; // nach der Klasse des Objektes folgt im file der Name
				file >> word; // Attribut nach dem Namen
				s_stream << word; // Umwandlung ist notwendig um den Winkel als float zu extrahieren
				float c_angle;
				s_stream >> c_angle;
				s_stream.clear(); // stream wird geleert nach Nutzung

				file >> word;
				if (word != "render" && word != "camera" && word != "define") // Abfangen von Zusatzinformationen zur Camera für erweitertes Kameramodel
				{
					float x,y,z; // x,y,z für eye
					s_stream << word << ' ';
					file >> word;
					s_stream << word << ' ';
					file >> word;
					s_stream << word;
					s_stream >> x >> y >> z;
					glm::vec3 c_eye(x,y,z);
					s_stream.clear();
					file >> word;

					s_stream << word << ' ';
					file >> word;
					s_stream << word << ' ';
					file >> word;
					s_stream << word;
					s_stream >> x >> y >> z;
					glm::vec3 c_dir(x,y,z);
					s_stream.clear();
					file >> word;

					s_stream << word << ' ';
					file >> word;
					s_stream << word << ' ';
					file >> word;
					s_stream << word;
					s_stream >> x >> y >> z;
					glm::vec3 c_up(x,y,z);
					s_stream.clear();

					Camera c{name, c_angle, c_eye, c_dir, c_up}; // Kamera mit vollem Konstruktor
					s.cam = c;
				}
				else{
					Camera c{name, c_angle}; // Kamera mit Konstruktor mit Name und Blickwinkel
					s.cam = c;
				}
			}
			//Material
			/*
			else if(word.compare("material") == 0){
				float r,g,b;
				file >> name;
				if( s.material.find(name) == s.material.end()){

					//ka
					s_stream.clear();
		 			file >> word;
		 			s_stream << word << ' ';
		 			file >> word;
		 			s_stream << word << ' ';
		 			file >> word;
		 			s_stream << word;
		 			s_stream >> r >> g >> b;
		 			Color ka(r,g,b);
		 			s_stream.clear();
		 			
		 			// kd
		 			file >> word;
		 			s_stream << word << ' ';
		 			file >> word;
		 			s_stream << word << ' ';
		 			file >> word;
		 			s_stream << word;
		 			s_stream >> r >> g >> b;
		 			Color kd(r,g,b);
		 			s_stream.clear();

		 			// ks
		 			file >> word;
		 			s_stream << word << ' ';
		 			file >> word;
		 			s_stream << word << ' ';
		 			file >> word;
		 			s_stream << word;
		 			s_stream >> r >> g >> b;
		 			Color ks(r,g,b);
		 			s_stream.clear();

		 			float m;
		 			file >> word;
		 			s_stream << word << ' ';
		 			file >> word;
		 			s_stream << word << ' ';
		 			file >> word;
		 			s_stream << word;
		 			s_stream >> m;
		 			s_stream.clear();

			 		Material mat{name, ka, kd, ks, m};
					s.material[name] = mat;
		 			
				}
			}
			*/
			//nächstes Element
		}
	}
	else{
 		std::cout << "bad file" << std::endl;
	}
		return s;
}