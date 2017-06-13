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
      this->addLight(light);
}

Scene0::~Scene0()
{
  delete mesh;
  delete light;
}

void Scene0::Update(float deltaTime)
{

}
