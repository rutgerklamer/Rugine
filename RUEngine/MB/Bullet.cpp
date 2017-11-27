#include "Bullet.h"


Bullet::Bullet(glm::vec3 direction) : Entity()
{
  this->dir = direction;
  this->LoadObject("Assets/untitled.obj", false);
  this->scale  = glm::vec3(0.3,0.3,0.3);
  this->setColor(glm::vec3(0,0,1));
  this->reflective = true;
}

Bullet::~Bullet()
{

}

void Bullet::update(float deltaTime) {
  this->position += dir  * deltaTime;
}

void Bullet::mirrorDir()
{
  this->dir = -dir;
}
