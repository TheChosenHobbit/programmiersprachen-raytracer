#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "sphere.hpp"
#include "box.hpp"
#include <cmath>
#include "shape.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

TEST_CASE ("Sphere Area and Volume","[Sphere]"){
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
	Color red {1,0,0};
	Sphere s{{"Sphere"}, {red}, {1,1,1}, {2}};
	std::cout << s;
	Box b {{"Box"},{red}, {1,1,1}, {2,2,2}};
	std::cout << b;
}

TEST_CASE("intersectRaySphere","[intersect]"){
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

TEST_CASE("example", "[aufgabe 7 ]"){
	Color red(255, 0, 0);
	glm::vec3 position(0.0, 0.0, 0.0);

	std::shared_ptr<Sphere> s1 = std::make_shared<Sphere>("sphere0", red, position, 1.2f);
	std::shared_ptr<Shape> s2 = std::make_shared<Sphere>("sphere1", red, position, 1.2f);

	s1->print(std::cout);
	s2->print(std::cout);
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
