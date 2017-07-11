#include "Scene.h"

Scene::Scene(Input* input) : Superscene(input)
{
  std::cout << "Scene initialized" << std::endl;
  //Create a mesh
      mesh = new Entity();
      mesh->LoadObject("Assets/dragon.obj", false);
      //Set a texture to it
      mesh->setTexture(tex::loadTexture("Assets/wall.jpg"));
      mesh->position = glm::vec3(0,0,0);
      //Add a child to the stage
      this->addChild(mesh);

      light = new Light();
      light->position = glm::vec3(5,5,5);
      light->setPosition(light->getPosition());
      light->setLightColor(glm::vec3(0.42f,0.55,0.09));
      light->setStrength(2.5f);
      light->setSpecularStrength(4.0f);
      this->addLight(light);

      light2 = new Light();
      light2->position = glm::vec3(-5,5,5);
      light2->setPosition(light2->getPosition());
      light2->setLightColor(glm::vec3(0.80, 0.36, 0.36));
      light2->setStrength(5.5f);
      this->addLight(light2);

      std::cout << "making" << std::flush;
      skybox = new Skybox("Assets/mountain_rt.tga", "Assets/mountain_lf.tga", "Assets/mountain_up.tga", "Assets/mountain_dn.tga", "Assets/mountain_bk.tga", "Assets/mountain_ft.tga");
      std::cout << "created" << std::flush;
      this->addSkybox(skybox);



      setGamma(0.5f);
      setExposure(0.3f);
}

Scene::~Scene()
{
  delete mesh;
  delete light;
  delete skybox;
}

void Scene::Update(float deltaTime)
{
  mesh->eularAngles.y += 0.1* deltaTime;
}
