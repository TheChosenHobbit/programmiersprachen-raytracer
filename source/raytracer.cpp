#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>
#include "scene.hpp"
#include "sdf_loader.hpp"

int main(int argc, char* argv[])
{
  unsigned const width = 800;
  unsigned const height = 800;
  /*
  for (int i = 1; i <= 120; ++i)
  {
  std::string const filename = "./animation"+i+".ppm";

  Sdf_loader loader;
  Scene scene = loader.load_scene("/home/david/Git/raytracer/programmiersprachen-raytracer/animation"+i+".txt");

  Renderer app(width, height, filename, scene);
  app.render();

  std::thread thr([&app]() { app.render(); });

  }
*/
  std::string const filename = "./checkerboard.ppm";

  Sdf_loader loader;
  Scene scene = loader.load_scene("/home/david/Git/raytracer/programmiersprachen-raytracer/testload.txt");

  Renderer app(width, height, filename, scene);
  app.render();

  std::thread thr([&app]() { app.render(); });

  Window win(glm::ivec2(width,height));

  while (!win.shouldClose()) {
    if (win.isKeyPressed(GLFW_KEY_ESCAPE)) {
      win.stop();
    }

    glDrawPixels( width, height, GL_RGB, GL_FLOAT
                , app.colorbuffer().data());

    win.update();
  }

  thr.join();

  return 0;
}
