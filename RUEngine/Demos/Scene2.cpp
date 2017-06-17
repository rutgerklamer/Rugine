#include "Scene2.h"

Scene2::Scene2(Input* input) : Superscene(input)
{
      std::cout << "Scene2 initialized" << std::endl;
      //Create a mesh
      mesh = new Entity();
      mesh->LoadObject("Assets/head.obj", true);
      //Set a texture to it
      mesh->setTexture(tex::loadTexture("Assets/lambertian.jpg"));
      mesh->setNormalMap(tex::loadTexture("Assets/bumps.jpg"));
      mesh->position = glm::vec3(0,0,0);
      //Add a child to the stage
      this->addChild(mesh);

      light = new Light();
      light->position = glm::vec3(0,0,10);
      light->setPosition(light->getPosition());
      light->setLightColor(glm::vec3(1,1,1));
      light->setStrength(2.5f);
      light->setSpecularStrength(2.0f);
      this->addLight(light);

      setGamma(0.8f);
      setExposure(0.4f);
}

Scene2::~Scene2()
{
  delete mesh;
  delete light;
}

void Scene2::Update(float deltaTime)
{
}
