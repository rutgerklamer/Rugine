#include "Scene1.h"

Scene1::Scene1(Input* input) : Superscene(input)
{
  std::cout << "Scene1 initialized" << std::endl;
  //Create a mesh
      mesh = new Entity();
      mesh->LoadObject("Assets/bunny.obj", false);
      //Set a texture to it
      mesh->setTexture(tex::loadTexture("Assets/szclcdi.png"));
      mesh->position = glm::vec3(0,0,0);
      mesh->scale = glm::vec3(10,10,10);
      mesh->showNormals = true;
      //Add a child to the stage
      this->addChild(mesh);

      light = new Light();
      light->position = glm::vec3(5,5,5);
      light->setPosition(light->getPosition());
      light->setLightColor(glm::vec3(1,0,1));
      light->setStrength(1.5f);
      light->setSpecularStrength(2.0f);
      this->addLight(light);

      setGamma(1.8f);
      setExposure(0.25f);
}

Scene1::~Scene1()
{
  delete mesh;
  delete light;
}

void Scene1::Update(float deltaTime)
{

}
