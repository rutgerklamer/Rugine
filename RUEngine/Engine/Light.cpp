#include "Light.h"

Light::Light() : Entity()
{
  std::cout << "Light initialized" << std::endl;
  this->lightColor = glm::vec3(1,1,1);
}

Light::~Light()
{

}

glm::vec3 Light::getLightColor()
{
  return this->lightColor;
}

void Light::setLightColor(glm::vec3 color)
{
  this->lightColor = color;
}
