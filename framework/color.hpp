// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Color
// -----------------------------------------------------------------------------

#ifndef BUW_COLOR_HPP
#define BUW_COLOR_HPP

#include <iostream>

struct Color
{
  Color() : r(0.0f), g(0.0f), b(0.0f) {}

  Color(float red, float green, float blue) :
  r(red),
  g(green),
  b(blue) {}
  
  float r;
  float g;
  float b;

  friend std::ostream& operator<<(std::ostream& os, Color const& c)
  {
    os << "(" << c.r << "," << c.g << "," << c.b << ")\n";
    return os;
  }

  Color& operator+=(Color const& other)
  {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
  }

  Color& operator-=(Color const& other)
  {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
  }

  Color& operator *=(Color const& other)
  {
    r *= other.r;
    g *= other.g;
    b *= other.b;
    return *this;
  }

  Color& operator*=(float const& other){
    r *= other;
    g *= other;
    b *= other;
    return *this;
  }

  friend Color operator+(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp += b;
    return tmp;
  }

  friend Color operator-(Color const& a, Color const& b)
  {
    auto tmp(a);
    tmp -= b;
    return tmp;
  }

  friend Color operator*(Color const& a, float const& b){
    auto tmp(a);
    tmp *= b;
    return tmp;
  }
  
  friend Color operator*(Color const& a, Color const& b){
    auto tmp(a);
    tmp *= b;
    return tmp;
  }

  friend Color operator*(float factor, Color const& col)
  {
    float r = col.r*factor;
    float g = col.g*factor;
    float b = col.b*factor;
    Color color{r, g, b};
    return color;
  }

  friend bool operator==(Color const& a, Color const& b)
  {
    return ((a.r==b.r) && (a.g==b.g) && (a.b==b.b));
  }

  Color& operator= (Color const& other){
    r = other.r;
    g = other.g;
    b = other.b;
    return *this;
  }

};

#endif //#define BUW_COLOR_HPP
