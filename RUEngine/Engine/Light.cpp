#include "Light.h"

Light::Light() : Entity()
{
  std::cout << "Light initialized" << std::endl;
  this->lightData.lightColor = glm::vec3(1,1,1);
}

Light::~Light()
{

}

LightData Light::getLightData()
{
  return this->lightData;
}

void Light::setLightColor(glm::vec3 color)
{
  this->lightData.lightColor = color;
}

void Light::setStrength(int strength)
{
  this->lightData.lightStrength = strength;
}

void Light::setPosition(glm::vec3 position)
{
  this->lightData.lightPosition = position;
}
