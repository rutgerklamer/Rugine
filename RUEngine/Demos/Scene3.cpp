#include "Scene3.h"

Scene3::Scene3(Input* input) : Superscene(input)
{
      std::cout << "Scene3 initialized" << std::endl;
      //Create a mesh
      mesh = new Entity();
      mesh->LoadObject("Assets/africanHead.obj", true);
      //Set a texture to it
      mesh->setTexture(tex::loadTexture("Assets/africanHead.tga"));
      mesh->setNormalMap(tex::loadTexture("Assets/africanHeadNM.tga"));
      mesh->position = glm::vec3(0,0,0);
      mesh->scale = glm::vec3(10,10,10);
      //Add a child to the stage
      this->addChild(mesh);

      light = new Light();
      light->position = glm::vec3(0,20,20);
      light->setPosition(light->getPosition());
      light->setLightColor(glm::vec3(1,1,1));
      light->setStrength(4.5f);
      light->setSpecularStrength(2.0f);
      this->addLight(light);

      setGamma(0.8f);
      setExposure(0.3f);
}

Scene3::~Scene3()
{
  delete mesh;
  delete light;
}

void Scene3::Update(float deltaTime)
{
  mesh->eularAngles.y += 0.1* deltaTime;
}
