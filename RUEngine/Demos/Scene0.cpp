#include "Scene0.h"

Scene0::Scene0(Input* input) : Superscene(input)
{
      std::cout << "Scene0 initialized" << std::endl;
      //Create a mesh
      mesh = new Entity();
      mesh->LoadObject("Assets/sponza.obj", false);
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
      light->setStrength(3.0f);
      light->setSpecularStrength(3.0f);
      this->addLight(light);

      for (int i = 0; i < 8; i++) {
        Light* light2 = new Light();
        light2->position = glm::vec3(-35 + (i * 10),2,0);
        light2->setPosition(light2->getPosition());
        light2->setLightColor(glm::vec3(sin(i * 16.0f),cos(i*16.0f),i/16.0f));
        light2->setStrength(i);
        light2->setExtinction(i / 2);
        light2->setSpecularStrength(2.0f);
        this->addLight(light2);
      }

      setGamma(1.2f);
      setExposure(0.20f);
      skybox = new Skybox("Assets/sandtrap_rt.tga", "Assets/sandtrap_lf.tga", "Assets/sandtrap_up.tga", "Assets/sandtrap_dn.tga", "Assets/sandtrap_bk.tga", "Assets/sandtrap_ft.tga");
      this->addSkybox(skybox);
}

Scene0::~Scene0()
{
  delete mesh;
  delete light;
}

void Scene0::Update(float deltaTime)
{
  std::cout << sizeof(long) << std::endl;
}
