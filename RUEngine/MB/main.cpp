#include <iostream>
#include <GL/glew.h>
#include "glfw3.h"
#include <vector>

#include "Engine/Display.h"
#include "MB/Scene.h"
#include "MB/Scene1.h"
#include "MB/StartMenu.h"

// Declare types
Display* display;
Scene* scene;
Scene1* scene1;
StartMenu* startscene;

int main()
{
  // Make a new Display, This will load all necessary framework related classes
  display = new Display();
  // Make the scenes we have and give them the input display created for us
  startscene = new StartMenu(display->input);
  scene = new Scene(display->input);
  scene1 = new Scene1(display->input);
  // Add those scenes to the scenemanager
  display->addScene(startscene);
  display->addScene(scene);
  display->addScene(scene1);
  // Start the main gameloop
  display->gameLoop();
  // If the gameloop stops we can delete everything we created here
  delete scene;
  delete scene1;
  delete startscene;
  delete display;
  std::cout << "Window closed" << std::endl;
  return 0;
}
