#include "Renderer.h"
#include "stdlib.h"

Renderer::Renderer()
{
  std::cout << "Renderer initialized" << std::endl;
}

Renderer::~Renderer()
{

}

void Renderer::render(double currentTime, Shader* shader, Camera* camera, Entity* entity, Light* light)
{
  glm::mat4 model;
  if (light != NULL) {
    LightData lightData = light->getLightData();
    //Send lights position;
    glUniform3f(glGetUniformLocation(shader->shaderProgram, "lightPos"), lightData.lightPosition.x, lightData.lightPosition.y, lightData.lightPosition.z);
    //Send cameras position

    glUniform3f(glGetUniformLocation(shader->shaderProgram, "camPos"), camera->getPosition().x,camera->getPosition().y,camera->getPosition().z);

    //Send light color (rgb)
    glUniform3f(glGetUniformLocation(shader->shaderProgram, "lightColor"), lightData.lightColor.x, lightData.lightColor.y, lightData.lightColor.z);
  }
//Manipulate model matrix
  model =  entity->getModelMatrix();
  //Send to vertex shader
  glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
  //Send a texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, entity->getTexture());

  //Bind the VAO of the mesh
  entity->Draw();

  //Draw the mesh
  glDrawArrays(GL_TRIANGLES, 0, entity->getSize());
}
