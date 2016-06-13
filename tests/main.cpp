#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "sphere.hpp"
#include "box.hpp"

TEST_CASE ("Sphere Area and Volume","[Sphere]"){
	Sphere s{{1.0,1.0,1.0},{2}};
	REQUIRE(s.area() == Approx(25.132));
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
