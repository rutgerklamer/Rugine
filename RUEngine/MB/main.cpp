#include <iostream>
#include <GL/glew.h>
#include "glfw3.h"
#include <vector>

#include "Engine/Display.h"
#include "MB/Scene.h"
#include "MB/Scene1.h"

Display* display;
Scene* scene;
Scene1* scene1;

int main()
{
  display = new Display();
  scene = new Scene(display->input);
  scene1 = new Scene1(display->input);
  display->addScene(scene);
  display->addScene(scene1);
  display->gameLoop();
  delete scene;
  delete scene1;
  delete display;
  std::cout << "Window closed" << std::endl;
  return 0;
}
