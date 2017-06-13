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
  //Get the view matrix
  glm::mat4 view = camera->getViewMatrix();
  //Send view to the vertex shader
  glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
  //Set the default texture to position 0
  glUniform1i(glGetUniformLocation( shader->shaderProgram, "texture"),0);
}

void ResourceManager::setProjectionMatrix(Shader* shader, Camera* camera)
{
  shader->Use();
  //Get the projection
  glm::mat4 projection = camera->getProjectionMatrix();
  //Send projection to the vertex shader
  glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "proj"), 1, GL_FALSE, glm::value_ptr(projection));
}
