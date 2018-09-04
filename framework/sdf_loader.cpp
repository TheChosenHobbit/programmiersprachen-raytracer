#include "sdf_loader.hpp"

using namespace std;

sdf_loader::sdf_loader(std::string filename):
	filename_{filename}{}

sdf_loader::sdf_loader():
	filename_{""}{}

sdf_loader::~sdf_loader(){}

Scene sdf_loader::load_scene(std::string filename) const {
	ifstream file(filename, ios::in);
	Scene s{};
	std::string word = " ";
	std::string name = " ";
	std::stringstream s_stream;
	//std::map<std::string, std::shared_ptr<Shape>> shape_map;

	if(file.good()){
		while(file >> word){  //iteriert über die mit Leerzeichen getrennten "Wörter" im file
			if(word == "camera"){
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

			//nächstes Element
		}
	}
}