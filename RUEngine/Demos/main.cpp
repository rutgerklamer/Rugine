#include <iostream>
#include <GL/glew.h>
#include "glfw3.h"
#include <vector>

#include "Engine/Display.h"
#include "Demos/Scene.h"
#include "Demos/Scene0.h"
#include "Demos/Scene1.h"
#include "Demos/Scene2.h"
#include "Demos/Scene3.h"

Display* display;
Scene* scene;
Scene0* scene0;
Scene1* scene1;
Scene2* scene2;
Scene3* scene3;

int main()
{
  display = new Display();
  scene = new Scene(display->input);
  // scene0 = new Scene0(display->input);
  // scene1 = new Scene1(display->input);
   scene2 = new Scene2(display->input);
  scene3 = new Scene3(display->input);
  // display->addScene(scene);
  // display->addScene(scene0);
  // display->addScene(scene1);
   display->addScene(scene2);
  display->addScene(scene3);
  display->gameLoop();
  delete scene;
  delete scene0;
  delete scene1;
  delete scene2;
  delete scene3;
  delete display;
  std::cout << "Window closed" << std::endl;
  return 0;
}
