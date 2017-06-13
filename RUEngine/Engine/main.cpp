#include <iostream>
#include <GL/glew.h>
#include "glfw3.h"
#include "Display.h"

Display* display;

int main()
{
  display = new Display();
  delete display;
  std::cout << "Window closed" << std::endl;
  return 0;
}
