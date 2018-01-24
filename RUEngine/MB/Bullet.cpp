#include "Bullet.h"


Bullet::Bullet(glm::vec3 direction, Origin o) : Entity()
{
  // Set the direction
  this->dir = direction;
  // Load an OBJ file, set normal map to false
  this->LoadObject("Assets/untitled.obj", false);
  // Set the objects scale
  this->scale  = glm::vec3(0.7f,0.7f,0.7f);
  // Set the objects color
  this->setColor(glm::vec3(0,0,1));
  // Make the object reflective
  this->reflective = true;
  // Set the origin of the object
  origin = o;
  // Start a timer
  time.timer.start();
}

Bullet::~Bullet()
{

}

void Bullet::update(float deltaTime) {
  // Add the direction to the position, Multiple direction by deltaTime so we have the same speed no matter wha fps
  this->position += dir  * deltaTime;
  // Set the color according to sin and coswaves of the time. Gives a nice little effect
  this->setColor(glm::vec3(sin(glfwGetTime()*5.0f),cos(glfwGetTime()*5.0f),cos(glfwGetTime())));
}

void Bullet::mirrorDirX()
{
  // Mirror the direction, Called when colliding with a mirror
  this->dir.x = -dir.x;
}

void Bullet::mirrorDirZ()
{
  // Mirror the direction, Called when colliding with a mirror
  this->dir.z = -dir.z;
}
