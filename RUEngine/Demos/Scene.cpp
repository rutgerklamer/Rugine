#include "Scene.h"

Scene::Scene(Input* input) : Superscene(input)
{
  std::cout << "Scene initialized" << std::endl;
  //Create a mesh
      mesh = new Entity();
      mesh->LoadObject("Assets/dragon.obj");
      //Set a texture to it
      mesh->setTexture(tex::loadTexture("Assets/wall.jpg"));
      mesh->position = glm::vec3(0,0,0);
      mesh->showNormals = true;
      //Add a child to the stage
      this->addChild(mesh);

      light = new Entity();
      light->position = glm::vec3(5,5,5);
      this->addLight(light);
}

Scene::~Scene()
{
  delete mesh;
  delete light;
}

void Scene::Update(float deltaTime)
{
  mesh->eularAngles.y += 0.1* deltaTime;
  mesh->quaternation = glm::quat(mesh->eularAngles);
}
