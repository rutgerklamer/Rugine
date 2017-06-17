#include "Time.h"

Time::Time()
{
  std::cout << "Time initialized" << std::endl;
}

Time::~Time()
{

}

void Time::update()
{
  currentTime = glfwGetTime();
  dt = currentTime - previousTime;
  previousTime = glfwGetTime();
  fps++;
  if (currentTime - lastTime >= 1.0) {
      std::cout << "deltaTime ( " << getDeltatime() << " ) fps ( " << fps << " )" << std::endl;
      fps = 0;
      lastTime = glfwGetTime();
  }
}

int Time::getFPS()
{
  return this->fps;
}

float Time::getDeltatime()
{
  return this->dt;
}
