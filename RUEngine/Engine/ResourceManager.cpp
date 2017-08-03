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
  //Update camera
  camera->updateCameraVector();
  //Get the view matrix
  glm::mat4 view = camera->getViewMatrix();
  //Send view to the vertex shader
  glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
  //Set the default texture to position 0
  glUniform1i(glGetUniformLocation( shader->shaderProgram, "skybox"),0);
}

void ResourceManager::setProjectionMatrix(Shader* shader, Camera* camera)
{
  shader->Use();
  //Get the projection
  glm::mat4 projection = camera->getProjectionMatrix();
  //Send projection to the vertex shader
  glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "proj"), 1, GL_FALSE, glm::value_ptr(projection));
}

void ResourceManager::removeLights(Shader* shader)
{
  shader->Use();
  for (unsigned int i = 0; i < 15; i++)
  {
    //Since we use the same shader for every scene we need to remove previously set uniforms
    glUniform3f(glGetUniformLocation(shader->shaderProgram, ("lightData[" + std::to_string(i) + "].lightPos").c_str()), 0,0,0);
    glUniform3f(glGetUniformLocation(shader->shaderProgram, ("lightData[" + std::to_string(i) + "].lightColor").c_str()), 0,0,0);
    glUniform1f(glGetUniformLocation(shader->shaderProgram, ("lightData[" + std::to_string(i) + "].lightStrength").c_str()),  0);
    glUniform1i(glGetUniformLocation(shader->shaderProgram, ("lightData[" + std::to_string(i) + "].isLight").c_str()),  0);

  }
}
