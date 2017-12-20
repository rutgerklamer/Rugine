#include "Bullet.h"


Bullet::Bullet(glm::vec3 direction, Origin o) : Entity()
{
  this->dir = direction;
  this->LoadObject("Assets/untitled.obj", false);
  this->scale  = glm::vec3(0.7f,0.7f,0.7f);
  this->setColor(glm::vec3(0,0,1));
  this->reflective = true;
  origin = o;
  time.timer.start();
}

Bullet::~Bullet()
{

}

void Bullet::update(float deltaTime) {
  this->position += dir  * deltaTime;
  this->setColor(glm::vec3(sin(glfwGetTime()*5.0f),cos(glfwGetTime()*5.0f),cos(glfwGetTime())));
}

void Bullet::mirrorDirX()
{
  this->dir.x = -dir.x;
}

void Bullet::mirrorDirZ()
{
  this->dir.z = -dir.z;
}
