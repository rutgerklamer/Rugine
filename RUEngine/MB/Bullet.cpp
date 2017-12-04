#include "Bullet.h"


Bullet::Bullet(glm::vec3 direction) : Entity()
{
  this->dir = direction;
  this->make2D();
  this->scale  = glm::vec3(0.003f,0.003f,1.0f);
  this->setColor(glm::vec3(0,0,1));
  this->reflective = true;
}

Bullet::~Bullet()
{

}

void Bullet::update(float deltaTime) {
  this->position += dir  * deltaTime;
}

void Bullet::mirrorDirX()
{
  this->dir.x = -dir.x;
}

void Bullet::mirrorDirY()
{
  this->dir.y = -dir.y;
}
