#include <iostream>
#include <GL/glew.h>
#include "glfw3.h"
#include <vector>

#include "Engine/Display.h"
#include "MB/Scene.h"
#include "MB/Scene1.h"
#include "MB/StartMenu.h"

Display* display;
Scene* scene;
Scene1* scene1;
StartMenu* startscene;

int main()
{
  display = new Display();
  startscene = new StartMenu(display->input);
  scene = new Scene(display->input);
  scene1 = new Scene1(display->input);
  display->addScene(startscene);
  display->addScene(scene);
  display->addScene(scene1);
  display->gameLoop();
  delete scene;
  delete scene1;
  delete startscene;
  delete display;
  std::cout << "Window closed" << std::endl;
  return 0;
}
