#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "sphere.hpp"
#include "box.hpp"
#include "shape.hpp"
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtx/intersect.hpp>

/*
TEST_CASE ("Sphere Area and Volume","[Sphere]"){
	std::cout << "____________________Sphere___________________" << std::endl;
	Color red {1,0,0};
	Sphere s{{"test"},red,{1.0,1.0,1.0},{2}};
	REQUIRE(s.area() == Approx(4*M_PI*2));
	REQUIRE(s.volume() == Approx(4/3*M_PI*2*2*2));
	REQUIRE(s.getColor() == red);


	Sphere s1;
	REQUIRE(s1.area() == Approx(0));
	REQUIRE(s1.volume() == Approx(0));
	REQUIRE(s1.getName() == "Sphere");
}

TEST_CASE("Box Area und Volume","[Box]"){
	std::cout << "____________________Box___________________" << std::endl;
	Box b{{"Box"},{0,0,1},{1.0,1.0,1.0},{2.0,2.0,2.0}};
	REQUIRE(b.area() == Approx(6.0f));
	REQUIRE(b.volume() == Approx(1.0f));
	REQUIRE(b.getName() == "Box");

	Box b1{{"Box1"},{0,1,0},{2.0,2.0,2.0},{4.0,4.0,4.0}};
	REQUIRE(b1.area() == Approx(24.0f));
	REQUIRE(b1.volume() == Approx(8.0f));

	Box b2{{"Box2"},{1,0,0},{1.0,2.0,3.0},{-3.0,2.0,-1.0}};
	REQUIRE(b2.area() == Approx(32.0f));
	REQUIRE(b2.volume() == Approx(0.0f));
}

TEST_CASE("Print","[Ausgabe]"){
	std::cout << "____________________Ausgabe___________________" << std::endl;
	Color red {1,0,0};
	Sphere s{{"Sphere"}, {red}, {1,1,1}, {2}};
	std::cout << s;
	Box b {{"Box"},{red}, {1,1,1}, {2,2,2}};
	std::cout << b;
}

TEST_CASE("intersectRaySphere","[intersect]"){
	std::cout << "____________________intersect___________________" << std::endl;
	//Ray
	glm::vec3 ray_origin{0.0,0.0,0.0};
	//ray direction has to be normalized !
	//you can use:
	//	v = glm:: normalize(some_vector)
	glm::vec3 ray_direction{0.0 ,0.0 ,1.0};
	// Sphere
	glm::vec3 sphere_center{0.0 ,0.0 ,5.0};
	float sphere_radius{1.0};
	float distance{0.0};
	auto result = glm::intersectRaySphere(ray_origin, ray_direction, sphere_center,
		sphere_radius * sphere_radius,	// squared radius !!!
		distance);
	REQUIRE(distance == Approx(4.0f));
}

TEST_CASE("Statisch und Dynamisch", "[Aufgabe 7]"){
	std::cout << "____________________Aufgabe 7___________________" << std::endl;
	Color red(255, 0, 0);
	glm::vec3 position(0.0, 0.0, 0.0);

	std::shared_ptr<Sphere> s1 = std::make_shared<Sphere>("sphere0", red, position, 1.2f);
	std::shared_ptr<Shape> s2 = std::make_shared<Sphere>("sphere1", red, position, 1.2f);

	s1->print(std::cout);
	s2->print(std::cout);
	/* Die Klasse, die bei der Deklaration einer Variablen verwendet wird, wird auch als statische Klasse 
	dieser Variable bezeichnet.
	Die tatsächliche Klasse des Wertes, der durch die Variable referenziert wird, wird als dynamische Klasse
	dieser Variable bezeichnet. Normalerweise sind bei statisch getypten Sprachen statische und dynamische Klasse einer 
	Variablen identisch.
	Im Kontext der Vererbung erlauben statisch typisierte OO-Sprachen, dass die dynamische Klasse einer Variablen
	eine von der statischen Klasse abgeleitete Klasse sein kann 
}

	TEST_CASE("Virtual Dekonstructor", "[Dekonstructor]"){
		std::cout << "____________________Dekonstructor___________________" << std::endl;
		Color red(255, 0, 0);
		glm::vec3 position(0.0, 0.0, 0.0);

		Sphere* s1 = new Sphere("sphere0", red, position, 1.2f);
		Shape* s2 = new Sphere("sphere1", red, position, 1.2f);

		s1->print(std::cout);
		s2->print(std::cout);

		delete s1;
		delete s2;
		/*
MIT virtual  					OHNE virtual

Shape::Constructor				Shape::Constructor
Sphere::Constructor				Sphere::Constructor
Shape::Constructor				Shape::Constructor
Sphere::Constructor				Sphere::Constructor
Name: sphere0					Name: sphere0
Color: 255, 0, 0, 				Color: 255, 0, 0, 
Center: 0, 0, 0 				Center: 0, 0, 0
Radius: 1.2 					Radius: 1.2
Name: sphere1 					Name: sphere1
Color: 255, 0, 0,  				Color: 255, 0, 0, 
Center: 0, 0, 0 				Center: 0, 0, 0
Radius: 1.2 					Radius: 1.2
Sphere::Destructor 				Sphere::Destructor
Shape::Destructor 				Shape::Destructor
Sphere::Destructor
Shape::Destructor 				Shape::Destructor
		
	}

	/* Aufgabe 5.9 
	Klassenhierarchie vs. Objekthierarchie
	Eine Menge von Klassen, deren Elemente durch die Relation Spezialisierung bzw. Generalisierung miteinander in 
	Beziehung gesetzt sind, bezeichnet man als Klassenhierarchie, wenn jede Klasse höchstens eine Basisklasse besitzt.
	Basisklasse heißt eine Klasse von der durch Spezialisierung eine abgeleitete Klasse gebildet wurde.
	Quelle: http://www2.htw-dresden.de/~sobe/Vorjahre/Vo_Info2_Jg10/9_Klassenhierarchien.pdf

	Unter Objekthirarchie versteht man die partielle Ordnung auf der Menge der Objekte entsprechend der zwischen ihnen bestehenden 
	Kompositionsbeziehung ("part-of"-Beziehung). Komponenten werden dabei als Nachfolger des Objekts, dem sie angehören, 
	angeordnet. Objekthierarchien werden aufbauend auf komplexen Objekten gebildet und sind dynamisch, da sie zur Laufzeit
	durch Zuweisen, Erzeugen und Löschen von Objekten verändert werden können. Sie werden durch gerichtete Graphen dargestellt.

	Klassendiagramm vs. Objektdiagramm
	Beides Strukturdiagramme
	

	grafischen Darstellung (Modellierung) von Klassen, Schnittstellen sowie deren Beziehungen. 
	Eine Klasse ist in der Objektorientierung ein abstrakter Oberbegriff für die Beschreibung der gemeinsamen Struktur 
	und des gemeinsamen Verhaltens von Objekten (Klassifizierung). Sie dient dazu, Objekte zu abstrahieren.

	zeigt eine bestimmte Sicht auf die Struktur des modellierten Systems. Die Darstellung umfasst dabei 
	typischerweise Ausprägungsspezifikationen von Klassen und Assoziationen
	zeigt den aktuellen Zustand, d. h. die Belegung der Attribute, eines Objektes bzw. einer Klasse. 
	Da die Anzahl der Attribute sehr groß sein kann, ist es möglich, nur bestimmte Attribute aufzulisten, 
	welche für den Zweck, den man verdeutlichen möchte ausreichen.
		

*/
/*
TEST_CASE("box intersect", "[raytracer]"){
	Box box;
	Ray ray {{-2.0f, 1.0f, 0.5f},{2.0f, -0.7f, 0.0f}};
	float distance;
	glm::vec3 min = box.getMin();
	glm::vec3 max = box.getMax();

	REQUIRE(box.intersect(ray, distance));
	box.intersect(ray, distance);
	std::cout << "test" << distance << std::endl;

}
*/

TEST_CASE("box intersect", "[raytracer]"){
	Box box;
	Ray ray {{-2.0f, 1.0f, 0.5f},{2.0f, -0.7f, 0.0f}};
	float distance;
	glm::vec3 min = box.getMin();
	glm::vec3 max = box.getMax();

	REQUIRE(box.intersect(ray, distance));
	box.intersect(ray, distance);
	std::cout << "hi" << distance << std::endl;

}
int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
