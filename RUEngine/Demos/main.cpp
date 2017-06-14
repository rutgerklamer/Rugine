#include <iostream>
#include <GL/glew.h>
#include "glfw3.h"
#include <vector>

#include "Engine/Display.h"
#include "Demos/Scene.h"
#include "Demos/Scene0.h"
#include "Demos/Scene1.h"

Display* display;
Scene* scene;
Scene0* scene0;
Scene1* scene1;

int main()
{
  display = new Display();
  scene = new Scene(display->input);
  scene0 = new Scene0(display->input);
  scene1 = new Scene1(display->input);
  display->addScene(scene);
  display->addScene(scene0);
  display->addScene(scene1);
  display->gameLoop();
  delete scene;
  delete scene0;
  delete scene1;

  delete display;
  std::cout << "Window closed" << std::endl;
  return 0;
}
