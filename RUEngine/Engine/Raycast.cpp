#include "Raycast.h"

Raycast::Raycast(Camera* camera, Input* input)
{
  this->camera = camera;
  this->input = input;
  projection = camera->getProjectionMatrix();
  std::cout << "Raycast initialized" << std::endl;
}

Raycast::~Raycast()
{

}

void Raycast::Update()
{
  view = camera->getViewMatrix();

  mouse = input->getMousePosition();
  //std::cout << " X ( " << mouse.x << " Y ( " << mouse.y << " )" << std::endl;
  mouse.x = (2.0f * mouse.x) / input->getWindowSize().x - 1.0f;
  mouse.y = (2.0f * mouse.y) / input->getWindowSize().y - 1.0f;
  glm::vec4 clipCoords = glm::vec4(mouse.x, mouse.y, -1.0f, 1.0f);

  glm::mat4 invertedProjection = glm::inverse(projection);
	glm::vec4 eyeCoords = invertedProjection * clipCoords;
	eyeCoords = glm::vec4(eyeCoords.x, eyeCoords.y, -1.0f, 0.0f);

  glm::mat4 invertedView = glm::inverse(view);
	glm::vec4 rayWorld = invertedView * eyeCoords;
	mouseRay = glm::normalize(glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z));

}

void Raycast::setCamera(Camera* camera)
{
  this->camera = camera;
  projection = camera->getProjectionMatrix();
}

void Raycast::checkCollision(Entity* entity)
{
  float distance  = 0.5f;
  std::cout << camera->getPosition().x << std::endl;
  glm::vec3 camPos = camera->getPosition();
	glm::vec3 scaledRay = camera->getFront();

  glm::vec3 checkPoint = entity->position;
  float radius = 0;
    if (entity->meshData.max.x * entity->scale.x > radius)
    {
      radius = entity->meshData.max.x;
    }
    if (entity->meshData.max.y * entity->scale.y > radius)
    {
      radius = entity->meshData.max.y;
    }
    if (entity->meshData.max.z * entity->scale.z > radius)
    {
      radius = entity->meshData.max.z;
    }

    for (unsigned int i = 0; i < 100; i++)
    {
      if (glm::length(camPos - checkPoint) < radius)
      {
        std::cout << i << "   " << radius << "   " << glm::length(camPos - checkPoint) << "    " << camPos.x << std::endl;
      }
      camPos += scaledRay;
    }
}
