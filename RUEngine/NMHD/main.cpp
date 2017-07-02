#include <iostream>
#include <GL/glew.h>
#include "glfw3.h"
#include <vector>

#include "Engine/Display.h"
#include "Demos/Scene.h"
#include "Demos/Scene0.h"

Display* display;
Scene* scene;
Scene0* scene0;

int main()
{
  display = new Display();
  scene = new Scene(display->input);
  scene0 = new Scene0(display->input);
  display->addScene(scene);
  display->addScene(scene0);
  display->gameLoop();
  delete scene;
  delete scene0;
  delete display;
  std::cout << "Window closed" << std::endl;
  return 0;
}
