#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
  std::cout << "ResourceManager initialized" << std::endl;
}

ResourceManager::~ResourceManager()
{

}

void ResourceManager::updateShaders(Shader* shader, Camera* camera)
{
  //Use shader program we send in the arguments
  shader->Use();
  //Get the projection matrix
  glm::mat4 projection = camera->getProjectionMatrix();
  //Get the view matrix
  glm::mat4 view = camera->getViewMatrix();
  //Send both to the vertex shader
  glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
  glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "proj"), 1, GL_FALSE, glm::value_ptr(projection));
}
