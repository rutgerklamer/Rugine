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

      light = new Light();
      light->position = glm::vec3(5,5,5);
      light->setPosition(light->getPosition());
      light->setLightColor(glm::vec3(1,0,1));
      light->setStrength(1.5f);
      this->addLight(light);

      light2 = new Light();
      light2->position = glm::vec3(-5,5,5);
      light2->setPosition(light2->getPosition());
      light2->setLightColor(glm::vec3(0,1,0));
      light2->setStrength(1.5f);
      this->addLight(light2);


      setGamma(0.5f);
      setExposure(0.45f);
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
