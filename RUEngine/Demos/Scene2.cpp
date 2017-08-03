#include "Scene2.h"

Scene2::Scene2(Input* input) : Superscene(input)
{
      std::cout << "Scene2 initialized" << std::endl;
      //Create a mesh
      mesh = new Entity();
      mesh->LoadObject("Assets/untitled.obj", true);
      //Set a texture to it
      mesh->setColor(glm::vec3(1.0,0.0,0.0));
      mesh->position = glm::vec3(0,10,0);
      mesh->scale = glm::vec3(1,1,1);
      //Add a child to the stage
      this->addChild(mesh);

      mesh2 = new Entity();
      mesh2->LoadObject("Assets/untitled.obj", true);
      //Set a texture to it
      mesh2->setColor(glm::vec3(0.0,1.0,0.0));
      mesh2->position = glm::vec3(0,0,0);
      mesh2->scale = glm::vec3(10,1,10);
      //Add a child to the stage
      this->addChild(mesh2);

      light = new Light();
      light->position = glm::vec3(0,20,0);
      light->setPosition(light->getPosition());
      light->setLightColor(glm::vec3(1,1,1));
      light->setStrength(2.5f);
      light->setSpecularStrength(1.2f);
      this->addLight(light);

      setGamma(0.8f);
      setExposure(0.3f);
}

Scene2::~Scene2()
{
  delete mesh;
  delete light;
}

void Scene2::Update(float deltaTime)
{

}
