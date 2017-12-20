#include "Renderer.h"
#include "stdlib.h"

Renderer::Renderer()
{
  std::cout << "Renderer initialized" << std::endl;
  Texture = tex::loadTexture("Assets/wall.jpg");
}

Renderer::~Renderer()
{

}

void Renderer::renderWater(Shader* shader, GLuint reflectionTexture, GLuint refractionTexture, GLuint waterTexture, GLuint normalTexture,  Entity* entity)
{
  shader->Use();
  glm::mat4 model;
  glUniform1f(glGetUniformLocation(shader->shaderProgram, "time"), glfwGetTime());
 //Manipulate model matrix
  model =  entity->getModelMatrix();
  //Send to vertex shader
  glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
  //Send a texture

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, reflectionTexture);
  glUniform1i(glGetUniformLocation(shader->shaderProgram, "WaterReflection"), 0);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, refractionTexture);
  glUniform1i(glGetUniformLocation(shader->shaderProgram, "WaterRefraction"), 1);
  glActiveTexture(GL_TEXTURE2);
  glBindTexture(GL_TEXTURE_2D, waterTexture);
  glUniform1i(glGetUniformLocation(shader->shaderProgram, "dudvMap"), 2);
  glActiveTexture(GL_TEXTURE3);
  glBindTexture(GL_TEXTURE_2D, normalTexture);
  glUniform1i(glGetUniformLocation(shader->shaderProgram, "normalMap"), 3);
  //Bind the VAO of the mesh
  entity->Draw();

  //Draw the mesh
  glDrawArrays(GL_TRIANGLES, 0, entity->getSize());
}

void Renderer::render2D(double currentTime, Shader* shader, Entity* entity)
{
  shader->Use();
  glm::mat4 model;
  model =  entity->getModelMatrix();
  glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

  if (entity != nullptr && entity->getColor().x + entity->getColor().y + entity->getColor().z == 0) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, entity->getTexture());
    glUniform1i(glGetUniformLocation(shader->shaderProgram, "Texture"), 0);
    glUniform3f(glGetUniformLocation(shader->shaderProgram, "Color"), 0, 0, 0);
  } else {
    glUniform3f(glGetUniformLocation(shader->shaderProgram, "Color"), entity->getColor().x, entity->getColor().y, entity->getColor().z);
  }
  entity->Draw();
  glDrawArrays(GL_TRIANGLES , 0, 6);
}


void Renderer::render(double currentTime, Shader* shader, Camera* camera, Entity* entity, SceneData scenedata, glm::vec4 waterPlane, std::vector<Light*>* lights)
{
  shader->Use();
  glm::mat4 model;
  if (lights != nullptr) {
    std::vector<Light*>& lightPointer = *lights;
    for (unsigned int i = 0; i < lightPointer.size(); i++) {
      LightData lightData = lightPointer[i]->getLightData();
      //Send lights position;
      glUniform3f(glGetUniformLocation(shader->shaderProgram, ("lightData[" + std::to_string(i) + "].lightPos").c_str()), lightData.lightPosition.x, lightData.lightPosition.y, lightData.lightPosition.z);
      //Send cameras position
      glUniform3f(glGetUniformLocation(shader->shaderProgram, "camPos"), camera->getPosition().x,camera->getPosition().y,camera->getPosition().z);
      //Send light color (rgb)
      glUniform3f(glGetUniformLocation(shader->shaderProgram, ("lightData[" + std::to_string(i) + "].lightColor").c_str()),  lightData.lightColor.x, lightData.lightColor.y, lightData.lightColor.z);
      //Send light strength
      glUniform1f(glGetUniformLocation(shader->shaderProgram, ("lightData[" + std::to_string(i) + "].lightStrength").c_str()),  lightData.lightStrength);
      //Send if there is a light
      //TODO remove
      glUniform1i(glGetUniformLocation(shader->shaderProgram, ("lightData[" + std::to_string(i) + "].isLight").c_str()),  1);
      glUniform1f(glGetUniformLocation(shader->shaderProgram, ("lightData[" + std::to_string(i) + "].specularStrength").c_str()),  lightData.specularStrength);
      glUniform1f(glGetUniformLocation(shader->shaderProgram, ("lightData[" + std::to_string(i) + "].extinction").c_str()),  lightData.extinction);

    }
  }
  //Send scene data
  glUniform1f(glGetUniformLocation(shader->shaderProgram, "sceneData.gamma"), scenedata.gamma);
  glUniform1f(glGetUniformLocation(shader->shaderProgram, "sceneData.exposure"), scenedata.exposure);
  if (scenedata.fogDensity > 0) {
    glUniform1f(glGetUniformLocation(shader->shaderProgram, "sceneData.fogDensity"), scenedata.fogDensity);
  } else {
    glUniform1f(glGetUniformLocation(shader->shaderProgram, "sceneData.fogDensity"), 0);
  }
  glUniform3f(glGetUniformLocation(shader->shaderProgram, "sceneData.fogColor"), scenedata.fogColor.x, scenedata.fogColor.y, scenedata.fogColor.z);
  glUniform1f(glGetUniformLocation(shader->shaderProgram, "time"), glfwGetTime());
  //Manipulate model matrix
  model =  entity->getModelMatrix();
  //Send to vertex shader
  glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
  glUniform4f(glGetUniformLocation(shader->shaderProgram, "planeYPosition"), waterPlane.x, waterPlane.y, waterPlane.z, waterPlane.w);
  //Send a texture

  if (entity != nullptr && entity->getColor().x + entity->getColor().y + entity->getColor().z == 0) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, entity->getTexture());
    glUniform1i(glGetUniformLocation(shader->shaderProgram, "Texture"), 0);
    glUniform3f(glGetUniformLocation(shader->shaderProgram, "Color"), 0, 0, 0);
    glUniform1f(glGetUniformLocation(shader->shaderProgram, "material.shininess"), entity->getShininess());
  } else {
    glUniform3f(glGetUniformLocation(shader->shaderProgram, "Color"), entity->getColor().x, entity->getColor().y, entity->getColor().z);
    glUniform1f(glGetUniformLocation(shader->shaderProgram, "material.shininess"), entity->getShininess());
  }
  if (entity->getNormalMap() != NULL) {
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, entity->getNormalMap());
    glUniform1i(glGetUniformLocation(shader->shaderProgram, "normalMap"), 1);
    glUniform1i(glGetUniformLocation(shader->shaderProgram, "hasNormalMap"), 1);
  } else {
    glUniform1i(glGetUniformLocation(shader->shaderProgram, "hasNormalMap"), 0);
  }

  //Bind the VAO of the mesh
  entity->Draw();

  //Draw the mesh
  if (entity->meshData.indsize != 0) {
    //std::cout << "indices" << std::endl;
    glDrawElements(GL_TRIANGLES, entity->meshData.indsize, GL_UNSIGNED_INT, 0);
  } else {
    glDrawArrays(GL_TRIANGLES, 0, entity->getSize());
  }
}


void Renderer::renderSkybox(double currentTime, Shader* shader, Camera* camera, Mesh* entity, SceneData scenedata, glm::vec4 waterPlane, GLuint skybox)
{
  shader->Use();

  glm::mat4 view;
  if (!entity->reflective && !entity->transparent) {
    glm::mat4 projection = camera->getProjectionOrthoMatrix();
    glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "proj"), 1, GL_FALSE, glm::value_ptr(camera->getProjectionMatrix()));

    glm::mat4 model;
    //Manipulate model matrix
    model =  glm::translate(model,glm::vec3(0,0,0));
    //Send to vertex shader
    glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    view = glm::mat4(glm::mat3(camera->getViewMatrix()));
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glCullFace(GL_FRONT);
    glDepthMask(GL_FALSE);
  } else {
    view = camera->getViewMatrix();
    //Send to vertex shader
    glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(entity->getModelMatrix()));
  }
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, skybox);
  glUniform1i(glGetUniformLocation(shader->shaderProgram, "skybox"), 0);
  glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
glUniform3f(glGetUniformLocation(shader->shaderProgram, "camPos"), camera->getPosition().x,camera->getPosition().y,camera->getPosition().z);
  glUniform4f(glGetUniformLocation(shader->shaderProgram, "planeYPosition"), waterPlane.x, waterPlane.y, waterPlane.z, waterPlane.w);
  //Send a texture


  if (entity->getColor().x + entity->getColor().y + entity->getColor().z == 0) {
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, entity->getTexture());
    glUniform1i(glGetUniformLocation(shader->shaderProgram, "Texture"), 1);
    glUniform3f(glGetUniformLocation(shader->shaderProgram, "Color"), 0, 0, 0);
  } else {
    glUniform3f(glGetUniformLocation(shader->shaderProgram, "Color"), entity->getColor().x, entity->getColor().y, entity->getColor().z);
  }
  //Bind the VAO of the mesh
  entity->Draw();

  //Draw the mesh
  glDrawArrays(GL_TRIANGLES, 0, entity->getSize());

  glDepthMask(GL_TRUE);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);
}

void Renderer::renderFramebuffer(Shader* shader, GLuint texture, Input* input)
{
  shader->Use();

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture);
  glUniform1i(glGetUniformLocation(shader->shaderProgram, "Texture"), 1);
  glm::vec2 velocity = input->getMouseVelocity();
  glUniform2f(glGetUniformLocation(shader->shaderProgram, "velocity"), velocity.x, velocity.y);

  glDrawArrays(GL_TRIANGLES , 0, 6);
}
