#include "Scene0.h"

Scene0::Scene0(Input* input) : Superscene(input)
{
  std::cout << "Scene0 initialized" << std::endl;
  //Create a mesh
      mesh = new Entity();
      mesh->LoadObject("Assets/sponza.obj");
      //Set a texture to it
      mesh->setTexture(tex::loadTexture("Assets/szclcdi.png"));
      mesh->position = glm::vec3(0,0,0);
      mesh->scale = glm::vec3(30,30,30);
      //Add a child to the stage
      this->addChild(mesh);

      light = new Light();
      light->position = glm::vec3(0,15,0);
      light->setPosition(light->getPosition());
      light->setLightColor(glm::vec3(0.4,0.1,0.2));
      this->addLight(light);

      setGamma(1.4f);
      setExposure(1.5f);
}

Scene0::~Scene0()
{
  delete mesh;
  delete light;
}

void Scene0::Update(float deltaTime)
{

}
