// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file): 
  width_(w),
  height_(h),
  colorbuffer_(w*h, Color(0.0, 0.0, 0.0)),
  filename_(file),
  ppm_(width_, height_){}


Renderer::Renderer(unsigned w, unsigned h, std::string const& file, Scene const& scene): 
  width_(w),
  height_(h),
  colorbuffer_(w*h, Color(0.0, 0.0, 0.0)),
  filename_(file),
  ppm_(width_, height_),
  scene_(scene){}

//old renderer, we added a new one
/*
void Renderer::render()
{
  const std::size_t checkersize = 20;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      if ( ((x/checkersize)%2) != ((y/checkersize)%2)) {
        p.color = Color(0.0, 1.0, float(x)/height_);
      } else {
        p.color = Color(1.0, 0.0, float(y)/width_);
      }

      write(p);
    }
  }
  ppm_.save(filename_);
}
*/

void Renderer::render(){

  Camera cam = scene_.camera;
  float width = (float)width_;      
  float half_height = ((float)height_) / 2;
  float half_width = ((float)width_) / 2;

  for(unsigned y = 0; y < height_; ++y){
    for (unsigned x = 0; x < width_; ++x){
      Pixel p(x,y);
      Color color{};

      //Antialiasing
      for(float i = 0.0f; i < 1.0f; i += 0.5f){
        for(float j = 0.0f; j < 1.0f; j += 0.5f){
    
          float y1 = (float)y + i;
          float x1 = (float)x + j;

          x1 = (x1 - half_width)/width;
          y1 = (y1 - half_height)/width;

          Ray camRay = cam.createRay(x1, y1);
          Color subcolor = raytrace(camRay);
          color += 0.25f * subcolor;
        }
      }
      
      p.color = color;
      write(p);
      
    }
  }
  ppm_.save(filename_);
}


void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= colorbuffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    colorbuffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}

//findet den ersten Hit unter allen Shapes
Hit Renderer::findHit(std::vector<std::shared_ptr<Shape>> const& shapes, Ray const& ray)
{
  Hit firstHit{};
  firstHit.distance_ = 100000000.0f;
  //macht ein intersect über jedes Shape
  for(auto it = shapes.begin(); it != shapes.end(); it ++){
    Hit hit = (**it).intersect(ray);
    //wenn getroffen wurde, wird verglichen ob es der näheste Treffer ist
    if (hit.is_hit_){
      hit.distance_ = glm::distance(hit.intersec_, ray.origin);
      if(firstHit.distance_ > hit.distance_){
        firstHit = hit;
      }
    }
  }
  return firstHit;
}

// Farbe wird anhand des Rays berechnet
Color Renderer::raytrace(Ray const& ray)
{
  Color color{};
  Hit camHit = findHit(scene_.shapes_ptr, ray);

  if(camHit.is_hit_ == false){
    color = scene_.backgroundcolor;
  } 
  else {

    Material mat = camHit.material_;

    color.r += mat.ka_.r * scene_.backgroundcolor.r; 
    color.g += mat.ka_.g * scene_.backgroundcolor.g;
    color.b += mat.ka_.b * scene_.backgroundcolor.b;

    for(auto it = scene_.lights.begin(); it != scene_.lights.end(); ++ it)
    {
      glm::vec3 lightVec = (*it).pos_ - camHit.intersec_; 
      lightVec = glm::normalize(lightVec);


      Ray lightRay;
      if(camHit.type_ == "sphere")
      {
        lightRay = {camHit.intersec_+ 0.01f * lightVec, lightVec};
      } 
      else if(camHit.type_ == "box"){
        lightRay = {(camHit.intersec_ + 0.01f * lightVec), lightVec};
      }
      Hit lightHits = findHit(scene_.shapes_ptr, lightRay);

      //Schatten
      if(!lightHits.is_hit_)
      {

          color.r += mat.kd_.r * (*it).ld_.r * (glm::dot(camHit.normvec_, lightRay.direction) + mat.ks_.r);
          color.g += mat.kd_.g * (*it).ld_.g * (glm::dot(camHit.normvec_, lightRay.direction) + mat.ks_.g);
          color.b += mat.kd_.b * (*it).ld_.b * (glm::dot(camHit.normvec_, lightRay.direction) + mat.ks_.b);
        
      }
    }
  }
  return color;
}
