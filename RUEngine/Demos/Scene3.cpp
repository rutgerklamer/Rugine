#include "Scene3.h"

Scene3::Scene3(Input* input) : Superscene(input)
{
  std::cout << "Scene3 initialized" << std::endl;
  //Create a mesh
      mesh = new Entity();
      mesh->LoadObject("Assets/teapot.obj", false);
      mesh->reflective = true;
      //Set a texture to it
      mesh->position = glm::vec3(0,0,0);
      mesh->setColor(glm::vec3(0.8,0.1,0.1));
      //Add a child to the stage
      this->addChild(mesh);


      mesh2 = new Entity();
      mesh2->LoadObject("Assets/bunny.obj", false);
      mesh2->reflective = true;
      //Set a texture to it
      mesh2->position = glm::vec3(5,0,0);
      mesh2->scale = glm::vec3(2.3,2.3,2.3);
      mesh2->setColor(glm::vec3(0.1,0.1,0.8));
      //Add a child to the stage
      this->addChild(mesh2);


      mesh3 = new Entity();
      mesh3->LoadObject("Assets/dragon.obj", false);
      mesh3->reflective = true;
      //Set a texture to it
      mesh3->position = glm::vec3(-5,0,0);
      mesh3->scale = glm::vec3(0.35,0.35,0.35);
      mesh3->setColor(glm::vec3(0.1,0.8,0.1));
      //Add a child to the stage
      this->addChild(mesh3);

      skybox = new Skybox("Assets/posx.jpg", "Assets/negx.jpg", "Assets/posy.jpg", "Assets/negy.jpg", "Assets/posz.jpg", "Assets/negz.jpg");
      this->addSkybox(skybox);

      setGamma(0.5f);
      setExposure(0.3f);
}

Scene3::~Scene3()
{
  delete mesh;
  delete mesh2;
  delete mesh3;
  delete skybox;
}

void Scene3::Update(float deltaTime)
{
  //mesh->eularAngles.y += 0.1* deltaTime;
}
