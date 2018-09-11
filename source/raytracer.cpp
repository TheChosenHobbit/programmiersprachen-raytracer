#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>
#include "scene.hpp"
#include "sdf_loader.hpp"

int main(int argc, char* argv[])
{
  unsigned const width = 600;
  unsigned const height = 600;
  std::string const filename = "./checkerboard.ppm";

  Sdf_loader loader;
  Scene scene = loader.load_scene("/home/IN/xavo6170/git/programmiersprachen-raytracer/testload.txt");

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
