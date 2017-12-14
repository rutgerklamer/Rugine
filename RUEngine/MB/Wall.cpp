#include "Wall.h"


Wall::Wall() : Entity()
{
  this->LoadObject("Assets/untitled.obj", false);
  this->setColor(glm::vec3(1,1,0));
  this->reflective = true;
}

Wall::~Wall()
{

}


void Wall::update(float deltaTime) {

}
