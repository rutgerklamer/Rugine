#include "Mirror.h"


Mirror::Mirror(float ma, float mi, bool z, glm::vec3 o) : Entity()
{
  // Load an OBJ file
  this->LoadObject("Assets/untitled.obj", false);
  // Set the color
  this->setColor(glm::vec3(0,0,1));
  // Make the object reflective
  this->reflective = true;
  // set these vars
  max = ma;
  min = mi;
  isZ = z;
  if (isZ) {
    // Object is vertical (Z axis)
    cur = this->position.z;
    this->scale  = glm::vec3(2.5f,7.5,10);
  } else {
    // Object is horizontal (X axis)
    cur = this->position.x;
    this->scale  = glm::vec3(10,7.5,2.5f);
  }
  // Set the origin so we can move the mirror according to this
  origin = o;
}

Mirror::~Mirror()
{

}

bool Mirror::checkZ()
{
  // Check if the mirror is horizontal or vertical
  return isZ;
}

void Mirror::update(float deltaTime) {
  if (input()->isDown(GLFW_KEY_S) && cur < max && !isZ || input()->isDown(GLFW_KEY_A) && cur < max && isZ) {
    // Move the mirror according to it's state (horizontal | vertical) 
    cur += 10.0f * deltaTime;
  } else if (input()->isDown(GLFW_KEY_W) && cur > min && !isZ || input()->isDown(GLFW_KEY_D) && cur > min && isZ) {
    // Move the mirror according to it's state (horizontal | vertical) 
    cur -= 10.0f * deltaTime;
  }
  if (isZ) {
    // Move the mirror according to it's state (horizontal | vertical) 
    this->position.z = origin.z + cur;
  } else {
    // Move the mirror according to it's state (horizontal | vertical) 
    this->position.x = origin.x + cur;
  }
}
