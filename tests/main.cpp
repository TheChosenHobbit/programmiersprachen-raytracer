#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "sphere.hpp"
#include "box.hpp"
#include <cmath>
#include "shape.hpp"
#include <iostream>

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

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
