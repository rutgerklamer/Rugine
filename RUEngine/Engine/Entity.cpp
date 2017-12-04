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
  if (!check2D()) {
    glm::mat4 model;
    model = glm::translate(model, position);
    model = glm::scale(model, scale);
    quaternation = glm::quat(eularAngles);
    glm::mat4 quat = glm::toMat4(quaternation);
    model = model*quat;
    return model;
  } else {
    glm::mat4 model;
    glm::vec3 p = glm::vec3((position.x * 2.0 - (1024.0f) )/ 1024.0f,(position.y * -2.0 + (720.0f) )/ 720.0f,0.0f);
    model = glm::translate(model, p);
    model = glm::scale(model, scale);
    quaternation = glm::quat(eularAngles);
    glm::mat4 quat = glm::toMat4(quaternation);
    model = model*quat;

    return model;
  }
}

glm::vec4 Entity::getScreenPosition()
{
  return glm::vec4((position.x * 2.0 - (1024.0f) )/ 1024.0f,(position.y * -2.0 + (720.0f) )/ 720.0f,0.0f,1.0f);
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
