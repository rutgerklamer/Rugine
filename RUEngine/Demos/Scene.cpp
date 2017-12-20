#include "Scene.h"

Scene::Scene(Input* input) : Superscene(input)
{
  std::cout << "Scene initialized" << std::endl;
  //Create a mesh
      mesh = new Entity();
      mesh->LoadObject("Assets/teapot.obj", false);
      mesh->transparent = true;
      //Set a texture to it
      mesh->setTexture(tex::loadTexture("Assets/wall.jpg"));
      mesh->position = glm::vec3(0,0,0);
      //Add a child to the stage
      this->addChild(mesh);

      skybox = new Skybox("Assets/sandtrap_rt.tga", "Assets/sandtrap_lf.tga", "Assets/sandtrap_up.tga", "Assets/sandtrap_dn.tga", "Assets/sandtrap_bk.tga", "Assets/sandtrap_ft.tga");
      this->addSkybox(skybox);

      setGamma(0.5f);
      setExposure(0.3f);
      addFramebuffer("Shaders/Framebuffer/shader.vert", "Shaders/Framebuffer/shader.frag");
}

Scene::~Scene()
{
  delete mesh;
  delete skybox;
}

void Scene::Update(float deltaTime)
{
if (input->getKeyDown(GLFW_KEY_RIGHT)) {
  sceneState = Superscene::NEXT;
}
if (input->getKeyDown(GLFW_KEY_LEFT)) {
  sceneState = Superscene::PREV;
}
  //mesh->eularAngles.y += 0.1* deltaTime;
}
