#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "color.hpp"
#include "ray.hpp"

class Shape
{

public: 

	Shape();
	Shape(std::string const& name, Color const& color);

	/*virtual*/ ~Shape();

    virtual float area() const = 0;
    virtual float volume() const = 0;

    std::string const& getName() const;
    Color const& getColor() const;

    virtual std::ostream& print(std::ostream& os) const;

    virtual bool intersect(Ray const& ray, float& t) const = 0;

protected:
	std::string name_;
	Color color_;
/*Alle Einträge in diesem Bereich können von der Basisklasse 
und allen abgeleiteten Klassen gesehen und manipuliert werden 
– allerdings nicht von außerhalb.*/

};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif //#define SHAPE_HPP