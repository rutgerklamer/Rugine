#include "Renderer.h"
#include "stdlib.h"

Renderer::Renderer()
{
  std::cout << "Renderer initialized" << std::endl;
}

Renderer::~Renderer()
{

}

void Renderer::render(double currentTime, Shader* shader, Camera* camera, Mesh* mesh, Mesh* light)
{
  glm::mat4 model;
  glm::mat4 quaternation;
  //Make the perspective projection

  if (light != NULL) {
    //Send lights position;
    glUniform3f(glGetUniformLocation(shader->shaderProgram, "lightPos"), light->getPosition().x, light->getPosition().y, light->getPosition().z);
    //Send cameras position

    glUniform3f(glGetUniformLocation(shader->shaderProgram, "camPos"), camera->getPosition().x,camera->getPosition().y,camera->getPosition().z);
  }
  //Send light color (rgb) + brightness (w)
  glUniform4f(glGetUniformLocation(shader->shaderProgram, "lightColor"), 1, 1, 1, 50);
  //Manipulate model matrix
  model =  mesh->getModelMatrix();
  //Send to vertex shader
  glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
  //Send a texture to the fragment shader
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, mesh->getTexture());
  glUniform1i(glGetUniformLocation( shader->shaderProgram, "texture"),0);

  glUniform1f(glGetUniformLocation( shader->shaderProgram, "time"),glfwGetTime());
  mesh->Draw();

  //Draw the mesh
  glDrawArrays(GL_TRIANGLES, 0, mesh->getSize());
  glDepthFunc(GL_LEQUAL);
}
