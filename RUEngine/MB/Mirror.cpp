#include "Mirror.h"


Mirror::Mirror(float ma, float mi, bool y, glm::vec3 o) : Entity()
{
  this->make2D();
  this->setColor(glm::vec3(0,0,1));
  this->reflective = true;
  isY = true;
  max = ma;
  min = mi;
  isY = y;
  if (isY) {
    cur = this->position.y;
    this->scale  = glm::vec3(0.01f,0.03f,1.0f);
  } else {
    cur = this->position.x;
    this->scale  = glm::vec3(0.03,0.01f,1.0f);
  }
  origin = o;
}

Mirror::~Mirror()
{

}

bool Mirror::checkY()
{
  return isY;
}

void Mirror::update(float deltaTime) {
  if (input()->isDown(GLFW_KEY_S) && cur < max && !isY || input()->isDown(GLFW_KEY_D) && cur < max && isY) {
    cur += 10.0f * deltaTime;
  } else if (input()->isDown(GLFW_KEY_W) && cur > min && !isY || input()->isDown(GLFW_KEY_A) && cur > min && isY) {
    cur -= 10.0f * deltaTime;
  }
  if (isY) {
    this->position.y = origin.y + cur;
  } else {
    this->position.x = origin.x + cur;
  }
}
