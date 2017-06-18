#include "Scene0.h"

Scene0::Scene0(Input* input) : Superscene(input)
{
  std::cout << "Scene0 initialized" << std::endl;
  //Create a mesh
  mesh = new Entity();
  mesh->LoadObject("Assets/head.obj", true);
  //Set a texture to it
  mesh->setTexture(tex::loadTexture("Assets/HeadColour.jpg"));
  mesh->setNormalMap(tex::loadTexture("Assets/Head_Level2_Normal.jpg"));
  mesh->position = glm::vec3(0,0,0);
  mesh->scale = glm::vec3(10,10,10);
  //Add a child to the stage
  this->addChild(mesh);

  light = new Light();
  light->position = glm::vec3(0,20,20);
  light->setPosition(light->getPosition());
  light->setLightColor(glm::vec3(1,1,1));
  light->setStrength(4.5f);
  light->setSpecularStrength(0.2f);
  this->addLight(light);

  setGamma(0.8f);
  setExposure(0.3f);
}

Scene0::~Scene0()
{
  delete mesh;
  delete light;
}

void Scene0::Update(float deltaTime)
{

}
