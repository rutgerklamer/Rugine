#include "Entity.h"

Entity::Entity() : Mesh()
{
  std::cout << "Entity initialized" << std::endl;
}

Entity::~Entity()
{

}

glm::mat4 Entity::getModelMatrix()
{
  glm::mat4 model;
  model = glm::translate(model, position);
  model = glm::scale(model, scale);
  glm::mat4 quat = glm::toMat4(quaternation);
  model = model*quat;
  return model;
}

glm::vec3 Entity::getPosition()
{
  return position;
}
