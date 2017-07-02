#include "Scene.h"
#include "stdlib.h"

struct cell {
  Entity* entity;
};

Scene::Scene(Input* input) : Superscene(input)
{
  rows = 10;
  std::cout << "Scene initialized" << std::endl;
  // for (unsigned int i =0; i < rows; i++) {
  //   for (unsigned int j = 0; j < rows; j ++) {
  //     if (rand() % 10 == 9 || rand() % 10 == 9) {
  //       //Create a mesh
  //       Entity* cell = new Entity();
  //       cell->LoadObject("Assets/untitled.obj", false);
  //       //Set a texture to it
  //       cell->setTexture(tex::loadTexture("Assets/dirt.jpg"));
  //       cell->position = glm::vec3(i,0,j);
  //       cell->scale = glm::vec3(0.5f,0.5f,0.5f);
  //       //Add a child to the stage
  //       this->addChild(cell);
  //       cells.push_back(cell);
  //     }
  //   }
  // }

  //Create a mesh
  mesh = new Entity();
  mesh->LoadObject("Assets/untitled.obj", false);
  //Set a texture to it
  mesh->setTexture(tex::loadTexture("Assets/dirt.jpg"));
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

Scene::~Scene()
{
  delete mesh;
  delete light;
}

void Scene::Update(float deltaTime)
{
  if (input->isDown(GLFW_KEY_W))
  {
    mesh->enabled = false;
  }

  for (unsigned int i =0; i < rows; i++) {
    for (unsigned int j = 0; j < rows; j ++) {
      int neighbours = 0;

    }
  }
}
