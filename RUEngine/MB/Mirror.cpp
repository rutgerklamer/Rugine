#include "Mirror.h"


Mirror::Mirror(float ma, float mi, bool z, glm::vec3 o) : Entity()
{
  this->LoadObject("Assets/untitled.obj", false);
  this->setColor(glm::vec3(0,0,1));
  this->reflective = true;
  isZ = true;
  max = ma;
  min = mi;
  isZ = z;
  if (isZ) {
    cur = this->position.z;
    this->scale  = glm::vec3(2.5f,10,10);
  } else {
    cur = this->position.x;
    this->scale  = glm::vec3(10,10,2.5f);
  }
  origin = o;
}

Mirror::~Mirror()
{

}

bool Mirror::checkZ()
{
  return isZ;
}

void Mirror::update(float deltaTime) {
  if (input()->isDown(GLFW_KEY_S) && cur < max && !isZ || input()->isDown(GLFW_KEY_D) && cur < max && isZ) {
    cur += 10.0f * deltaTime;
  } else if (input()->isDown(GLFW_KEY_W) && cur > min && !isZ || input()->isDown(GLFW_KEY_A) && cur > min && isZ) {
    cur -= 10.0f * deltaTime;
  }
  if (isZ) {
    this->position.z = origin.z + cur;
  } else {
    this->position.x = origin.x + cur;
  }
}
