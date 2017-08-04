#include "Superscene.h"

Superscene::Superscene(Input* input)
{
  this->input = input;
  camera = new Camera();
  std::cout << "Superscene initialized" << std::endl;
  sceneData.gamma = 1.6f;
  sceneData.exposure = 0.1f;
  sceneData.fogDensity = 0.0f;
  sceneData.fogColor = glm::vec3(0,0,0);
  skybox = NULL;
  framebuffer = NULL;
  water = nullptr;
}

Superscene::~Superscene()
{
  delete input;
  delete camera;
  for (unsigned int i = 0; i < entities.size(); i++)
  {
    delete entities[i];
  }
  for (unsigned int i = 0; i < lights.size(); i++)
  {
    delete lights[i];
  }
  delete skybox;
}

void Superscene::addSkybox(Skybox* sb)
{
  skybox = sb;
}

void Superscene::addFramebuffer(const char* vertexPath, const char* fragmentPath)
{
  framebuffer = new Framebuffer(vertexPath, fragmentPath);
}

void Superscene::addChild(Entity* mesh)
{
  entities.push_back(mesh);
}

void Superscene::addWater(Water* w)
{
  water = w;
}

void Superscene::addLight(Light* light)
{
  entities.push_back(light);
  lights.push_back(light);
}

void Superscene::Update(float deltaTime)
{
  for (unsigned int i = 0; i < entities.size(); i++)
  {
    entities[i]->update(deltaTime);
  }
}

SceneData Superscene::getSceneData()
{
  return this->sceneData;
}

void Superscene::setGamma(float gamma)
{
  this->sceneData.gamma = gamma;
}
void Superscene::setExposure(float exposure)
{
  this->sceneData.exposure = exposure;
}

void Superscene::setFogDensity(float density)
{
  this->sceneData.fogDensity = density;
}

void Superscene::setFogColor(glm::vec3 color)
{
  this->sceneData.fogColor = color;
}
