#ifndef BUW_MATERIAL_HPP
#define BUW_MATERIAL_HPP

#include <iostream>
#include "color.hpp"
#include <string>

struct Material
{
  Material() :
    name_(std::string("Material")), 
    ka_({0.0f, 0.0f, 0.0f}), 
    kd_({0.0f, 0.0f, 0.0f}),
    ks_({0.0f, 0.0f, 0.0f}),
    m_(0.0f) {}

  Material(std::string const& name, Color const& ka, Color const& kd, Color const& ks,  float m) :
    name_(name), 
    ka_(ka), 
    kd_(kd),
    ks_(ks),
    m_(m) {}

  std::string name_;
  Color ka_;
  Color kd_;
  Color ks_;
  float m_;



  friend std::ostream& operator<<(std::ostream& os, Material const& mat)
  {
    os << mat.name_ << "\nAmbient: " << mat.ka_ << "Diffuse:" << mat.kd_ << "Reflection:" << mat.ks_ << mat.m_ << std::endl;
    return os;
  }

};

#endif //#define BUW_MATERIAL_HPP