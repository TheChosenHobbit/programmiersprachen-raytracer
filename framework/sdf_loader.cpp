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
    	while(getline(myfile, line))
    	{
    		ss << line;
    		ss >> keyword;

    		if(keyword == "#")
    		{
    			continue;
    		}

    		if(keyword == "define")
    		{
    			ss >> keyword;

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
					std::cout << mat;
    			}


    			else if(keyword == "camera"){
                    std::string name;
                    float angle, pos_x, pos_y, pos_z, up_x, up_y, up_z;
                    ss >> name;
                    ss >> angle;
                    ss >> pos_x;
                    ss >> pos_y;
                    ss >> pos_z;
                    ss >> up_x;
                    ss >> up_y;
                    ss >> up_z;
                    glm::vec3 pos {pos_x, pos_y, pos_z};
                    glm::vec3 up {up_x, up_y, up_z};
                    

                    Camera cam {name, angle, pos, up}; //ohne direction
                    std::cout << cam;
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

                    std::cout << "test spast" << "\n";
                    ss >> brightness;
					Light licht {name, pos, ld, brightness};
                    s.lights.push_back(licht);
                    std::cout << "light: " << ld << "\n";
                }

                else if (keyword == "shape"){
                	ss >> keyword;
                	if (keyword == "box"){
                		std::string name;
                        std::string mat_namebox;
                        float min_x, min_y, min_z, max_x, max_y, max_z;
                        ss >> name;

                        ss >> min_x;
                        ss >> min_y;
                        ss >> min_z;
                        ss >> max_x;
                        ss >> max_y;
                        ss >> max_z;

                        glm::vec3 min{min_x, min_y, min_z};
                        glm::vec3 max{max_x, max_y, max_z};

                        ss >> mat_namebox;

                        std::shared_ptr<Shape> temp_ptr = std::make_shared<Box>
                        (
                            Box{name, s.materials[mat_namebox], min, max,}
                        );
                        std::cout << *temp_ptr;
                        s.shapes_ptr.push_back(temp_ptr);

                	}
                	if(keyword == "sphere"){
                        std::string name;
                        float x, y, z, r;
                        ss >> name;
                        ss >> x;
                        ss >> y;
                        ss >> z;
                        glm::vec3 center{x,y,z};
                        ss >> r;
                        std::string mat_name;
                        ss >> mat_name;

                        std::shared_ptr<Shape> temp_ptr = std::make_shared<Sphere>
                        (
                            Sphere{name, s.materials[mat_name], center, r}
                        );
                            std::cout << *temp_ptr;
                            s.shapes_ptr.push_back(temp_ptr);
                    }
                }

    		}
    		else if(keyword == "render"){
    			std::string name;
    			Camera camera;

    			ss >> name;
    			//check if the camera name is like the name of the camera used in renderer
    			if(name == camera.name_)
    			{
    				std::cout << "Name der Camera " << camera.name_ 
    				<< " ist gleich der vom Renderer " << name << "\n";
    			} else {
    				std::cout << "Namen der Camera und des eingelesenen Renderer stimmen nicht überein" << "\n";
    			}

                ss >> s.filename;
                ss >> s.x_res;
                ss >> s.y_res;
                std::cout << s.filename << "\n" <<"Resolution: "<< s.x_res << " x " << s.y_res << "\n";
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