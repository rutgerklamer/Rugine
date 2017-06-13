#include "Scene1.h"

Scene1::Scene1(Input* input) : Superscene(input)
{
  std::cout << "Scene1 initialized" << std::endl;
  //Create a mesh
      mesh = new Entity();
      mesh->LoadObject("Assets/bunny.obj");
      //Set a texture to it
      mesh->setTexture(tex::loadTexture("Assets/szclcdi.png"));
      mesh->position = glm::vec3(0,0,0);
      mesh->scale = glm::vec3(10,10,10);
      //Add a child to the stage
      this->addChild(mesh);



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
