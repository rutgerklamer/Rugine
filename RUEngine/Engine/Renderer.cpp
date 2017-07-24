#include "Renderer.h"
#include "stdlib.h"

Renderer::Renderer()
{
  std::cout << "Renderer initialized" << std::endl;
}

Renderer::~Renderer()
{

}

void Renderer::render(double currentTime, Shader* shader, Camera* camera, Entity* entity, SceneData scenedata, std::vector<Light*>* lights)
{
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
      //Send scene data
      glUniform1f(glGetUniformLocation(shader->shaderProgram, "sceneData.gamma"), scenedata.gamma);
      glUniform1f(glGetUniformLocation(shader->shaderProgram, "sceneData.exposure"), scenedata.exposure);
      glUniform1f(glGetUniformLocation(shader->shaderProgram, "sceneData.fogDensity"), scenedata.fogDensity);
      glUniform3f(glGetUniformLocation(shader->shaderProgram, "sceneData.fogColor"), scenedata.fogColor.x, scenedata.fogColor.y, scenedata.fogColor.z);
    }
  }
//Manipulate model matrix
  model =  entity->getModelMatrix();
  //Send to vertex shader
  glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
  //Send a texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, entity->getTexture());
  glUniform1i(glGetUniformLocation(shader->shaderProgram, "texture"), 0);
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
  glDrawArrays(GL_TRIANGLES, 0, entity->getSize());
}


void Renderer::renderSkybox(double currentTime, Shader* shader, Camera* camera, Mesh* entity, SceneData scenedata)
{


  shader->Use();

  glm::mat4 model;
//Manipulate model matrix
  model =  glm::translate(model,glm::vec3(0,0,0));
  //Send to vertex shader
  glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
  glm::mat4 view;
  if (!entity->reflective && !entity->transparent) {
    view = glm::mat4(glm::mat3(camera->getViewMatrix()));
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glCullFace(GL_FRONT);
    glDepthMask(GL_FALSE);
  } else {
    view = camera->getViewMatrix();
  }
  glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
  glm::mat4 projection = camera->getProjectionMatrix();
  glUniformMatrix4fv(glGetUniformLocation(shader->shaderProgram, "proj"), 1, GL_FALSE, glm::value_ptr(projection));
  glUniform3f(glGetUniformLocation(shader->shaderProgram, "camPos"), camera->getPosition().x,camera->getPosition().y,camera->getPosition().z);
  //Send a texture
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, entity->getTexture());
  glUniform1i(glGetUniformLocation(shader->shaderProgram, "skybox"), 0);
  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, entity->getTexture());
  glUniform1i(glGetUniformLocation(shader->shaderProgram, "Texture"), 1);
  //Bind the VAO of the mesh
  entity->Draw();

  //Draw the mesh
  glDrawArrays(GL_TRIANGLES, 0, entity->getSize());

  glDepthMask(GL_TRUE);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);
}
