#include "Scene1.h"

Scene1::Scene1(Input* input) : Superscene(input)
{
  std::cout << "Scene1 initialized" << std::endl;
  //Create a mesh
      mesh = new Entity();
      mesh->LoadObject("Assets/dragon.obj", false);
      //Set a texture to it
      mesh->setTexture(tex::loadTexture("Assets/wall.jpg"));
      mesh->position = glm::vec3(0,0,0);
      mesh->scale = glm::vec3(1,1,1);
      //Add a child to the stage
      this->addChild(mesh);

      light = new Light();
      light->position = glm::vec3(5,5,5);
      light->setPosition(light->getPosition());
      light->setLightColor(glm::vec3(0.42f,0.55,0.09));
      light->setStrength(2.5f);
      light->setSpecularStrength(9.0f);
      this->addLight(light);

      light2 = new Light();
      light2->position = glm::vec3(-5,5,5);
      light2->setPosition(light2->getPosition());
      light2->setLightColor(glm::vec3(0.80, 0.36, 0.36));
      light2->setStrength(9.5f);
      this->addLight(light2);

      setGamma(0.8f);
      setExposure(0.25f);
      skybox = new Skybox("Assets/sandtrap_rt.tga", "Assets/sandtrap_lf.tga", "Assets/sandtrap_up.tga", "Assets/sandtrap_dn.tga", "Assets/sandtrap_bk.tga", "Assets/sandtrap_ft.tga");
      this->addSkybox(skybox);
      water = new Water(glm::vec2(100,100), glm::vec3(0,1,0));
      addWater(water);
    // addFramebuffer("Shaders/Framebuffer/EdgeDetect/shader.vert", "Shaders/Framebuffer/EdgeDetect/shader.frag");

}

Scene1::~Scene1()
{
  delete mesh;
  delete light;
  delete light2;
}

void Scene1::Update(float deltaTime)
{

}
