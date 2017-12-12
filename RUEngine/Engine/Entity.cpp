#include "Entity.h"

Entity::Entity() : Mesh()
{
  eularAngles = glm::vec3(0,0,0);
  position = glm::vec3(0,0,0);
  scale = glm::vec3(1,1,1);
  quaternation = glm::mat4(1);

  //std::cout << "Entity initialized" << std::endl;
}

Entity::~Entity()
{

}

glm::mat4 Entity::getModelMatrix()
{
    glm::mat4 model;
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    quaternation = glm::quat(eularAngles);
    glm::mat4 quat = glm::toMat4(quaternation);
    model = model*quat;
    return model;
}

glm::mat4 Entity::getRotationScaleMatrix()
{
  glm::mat4 model;
  model = glm::translate(model, position);
  model = glm::scale(model, scale);
  quaternation = glm::quat(eularAngles);
  glm::mat4 quat = glm::toMat4(quaternation);
  model = model*quat;
  return model;
}

glm::mat4 Entity::getRotationMatrix()
{
  glm::mat4 model;
  model = glm::translate(model, position);
  quaternation = glm::quat(eularAngles);
  glm::mat4 quat = glm::toMat4(quaternation);
  model = model*quat;
  return model;
}

glm::mat4 Entity::getScaleMatrix()
{
  glm::mat4 model;
  model = glm::scale(model, scale);
  return model;
}

glm::quat Entity::getQuaternation()
{
  return quaternation;
}

glm::vec3 Entity::getPosition()
{
  return position;
}

void Entity::setInput(Input* i)
{
  _input = i;
}

Input* Entity::input()
{
  return _input;
}

void Entity::fixedUpdate(float deltaTime)
{
}

void Entity::update(float deltaTime)
{


}
