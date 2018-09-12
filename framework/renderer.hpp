// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "scene.hpp"
#include "color.hpp"
#include "pixel.hpp"
#include "ppmwriter.hpp"
#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "hit.hpp"
#include "shape.hpp"
#include "ray.hpp"

class Renderer
{
public:
  Renderer(unsigned w, unsigned h, std::string const& file);
  Renderer(unsigned w, unsigned h, std::string const& file, Scene const& s);


  void render();
  void write(Pixel const& p);

  Hit findHit(std::vector<std::shared_ptr<Shape>> const& shapes, Ray const& ray);
  Color raytrace(Ray const& ray);

  inline std::vector<Color> const& colorbuffer() const
  {
    return colorbuffer_;
  }

private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> colorbuffer_;
  std::string filename_;
  PpmWriter ppm_;
  Scene scene_;
};

#endif // #ifndef BUW_RENDERER_HPP
