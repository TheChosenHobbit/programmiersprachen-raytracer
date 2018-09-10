#include "sdf_loader.hpp"

sdf_loader::sdf_loader():
	filename_{""}{}

sdf_loader::sdf_loader(std::string filename):
	filename_{filename}{}

sdf_loader::~sdf_loader(){}

Scene sdf_loader::load_scene(std::string filename){
	Scene s;
	std::string line;
    std::ifstream myfile (filename);
    std::stringstream ss;
    std::string keyword;

    if(myfile.is_open())
    {
    	while(getline(myfile,line))
    	{
    		ss << line;
    		ss >> keyword;

    		if(keyword == "#")
    		{
    			continue;
    		}

    		if(keyword == "define")
    		{
    			ss>>keyword;
    			if(keyword == "material")
    			{
    				Material mat;
    				ss >> mat.name_;
    				ss >> mat.ka_.r;
                    ss >> mat.ka_.g;
                    ss >> mat.ka_.b;

                    ss >> mat.kd_.r;
                    ss >> mat.kd_.g;
                    ss >> mat.kd_.b;

                    ss >> mat.ks_.b;
                    ss >> mat.ks_.r;
                    ss >> mat.ks_.g;

                    ss >> mat.m_;

                    s.materials.insert({mat.name_, mat});
					//std::cout << mat;
    			}


    			else if(keyword == "camera"){
                    std::string name;
                    float angle, posx, posy, posz, upx, upy, upz;
                    ss >> name;
                    ss >> angle;
                    ss >> posx;
                    ss >> posy;
                    ss >> posz;
                    ss >> upx;
                    ss >> upy;
                    ss >> upz;
                    glm::vec3 pos {posx, posy, posz};
                    glm::vec3 up {upx, upy, upz};
                    

                    Camera cam {name, angle, pos, up}; //ohne direction
                    //std::cout << cam;
                    s.camera = cam;
                }

                else if(keyword == "light"){
                    std::string name;
                    float pos_x, pos_y, pos_z, ld_r, ld_g, ld_b, brightness;
                    ss >> name;
                    ss >> pos_x;
                    ss >> pos_y;
                    ss >> pos_z;
                    glm::vec3 pos{pos_x, pos_y, pos_z};
                    ss >> ld_r;
                    ss >> ld_g;
                    ss >> ld_b;
                    Color ld{ld_r, ld_g, ld_b};
                    ss >> brightness;

                    //TODO klappt das so?
                    Light light(name, pos, ld, brightness);
                    s.lights.push_back(light);

                    std::cout << "light: " << ld << "\n";
                }
    		}
    	}
    	myfile.close();
    }
    else
    {
    	std::cout << "Unable to open the file";
    }
    return s;
}

/*
Scene sdf_loader::load_scene(std::string const& filename){
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
			
			//nächstes Element
		}
	}
	else{
 		std::cout << "bad file" << std::endl;
	}
		return s;
}*/