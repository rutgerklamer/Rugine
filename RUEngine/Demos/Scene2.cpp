#include "Scene2.h"

Scene2::Scene2(Input* input) : Superscene(input)
{
      std::cout << "Scene2 initialized" << std::endl;
      //Create a mesh
      mesh = new Entity();
      mesh->LoadObject("Assets/untitled.obj", false);
      // mesh->setTexture(tex::loadTexture("Assets/HeadColour.jpg"));
      // mesh->setNormalMap(tex::loadTexture("Assets/Head_Level2_Normal.jpg"));
      //Set a texture to it
      mesh->position = glm::vec3(0,0,0);
      mesh->scale = glm::vec3(1,1,10);
      //Add a child to the stage
      this->addChild(mesh);

      light = new Light();
      light->position = glm::vec3(0,10,15);
      light->setPosition(light->getPosition());
      light->setLightColor(glm::vec3(1,1,1));
      light->setStrength(2.5f);
      light->setSpecularStrength(0.2f);
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
