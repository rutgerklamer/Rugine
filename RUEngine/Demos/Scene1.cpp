#include "Scene1.h"

Scene1::Scene1(Input* input) : Superscene(input)
{
  std::cout << "Scene1 initialized" << std::endl;
  //Create a mesh
      mesh = new Entity();
      mesh->LoadObject("Assets/m4a1.obj");
      //Set a texture to it
      mesh->setTexture(tex::loadTexture("Assets/wall.jpg"));
      mesh->position = glm::vec3(0,0,0);
      mesh->scale = glm::vec3(0.035,0.035,0.035);
      //Add a child to the stage
      this->addChild(mesh);

      mesh2 = new Entity();
      mesh2->LoadObject("Assets/dust2.obj");
      //Set a texture to it
      mesh2->setTexture(tex::loadTexture("Assets/dust.jpg"));
      mesh2->position = glm::vec3(0,0,0);
      mesh2->scale = glm::vec3(50.0,50.0,50.0);
      //Add a child to the stage
      this->addChild(mesh2);


      light = new Entity();
      light->position = glm::vec3(5,15,5);
      this->addLight(light);

      time->timer.start();
}

Scene1::~Scene1()
{
  delete mesh;
  delete light;
}

void Scene1::Update(float deltaTime)
{
  mesh->eularAngles.y = -glm::radians(camera->getYaw()) + 1.5;
  mesh->eularAngles.x = -glm::radians(camera->getPitch());
  mesh->quaternation = glm::quat(mesh->eularAngles);
  if (shooting)
  {
    mesh->position -= (mesh->position - camera->getPosition()) / 10.0f;
  } else {
    mesh->position = camera->getPosition();
  }
  if (shooting && time->timer.seconds() >= 0.05)
  {
    shooting = false;
  }

  if (input->isMouseDown(0))
  {
    input->setMouseKey(0, false);
    mesh->position += camera->getFront() / 2.0f;
    shooting = true;
    time->timer.start();
  }
}
