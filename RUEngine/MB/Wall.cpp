#include "Wall.h"


Wall::Wall() : Entity()
{
  // Load an OBJ file and set it as a mesh, we don't want it to have a normal map so we set it to false
  this->LoadObject("Assets/untitled.obj", false);
  // Set the color
  this->setColor(glm::vec3(1,1,0));
  // Make it reflective
  this->reflective = true;
}

Wall::~Wall()
{

}


void Wall::update(float deltaTime) {

}
