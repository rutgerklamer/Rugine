#include <iostream>
#include <GL/glew.h>
#include "glfw3.h"
#include <vector>

#include "Engine/Display.h"
#include "Demos/Scene.h"

Display* display;
Scene* scene;

int main()
{
  display = new Display();
  scene = new Scene(display->input);
  display->addScene(scene);
  display->gameLoop();
  delete scene;
  delete display;
  std::cout << "Window closed" << std::endl;
  return 0;
}
