#include "StartMenu.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iterator>

StartMenu::StartMenu(Input* input) : Superscene(input)
{
  hud = new Entity();
  hud->make2D();
  hud->scale  = glm::vec3(0.5,0.5,1);
  hud->setColor(glm::vec3(0,1,0));
  hud->position = glm::vec3(1024.0/3.0f,720/2.0f,0);
  this->addChild(hud);

  hud2 = new Entity();
  hud2->make2D();
  hud2->scale  = glm::vec3(0.5,0.5,1);
  hud2->setColor(glm::vec3(1,0,0));
  hud2->position = glm::vec3(1024 - 1024.0/3.0f,720/2.0f,0);
  this->addChild(hud2);
}

StartMenu::~StartMenu()
{

}

void StartMenu::Update(float deltaTime)
{
  if (Collision::intersectMouse2D(hud, glm::vec2(input->getMousePosition())) && input->getMouseKeyDown(0)) {
    sceneState = Superscene::NEXT;
  }
  if (Collision::intersectMouse2D(hud2, glm::vec2(input->getMousePosition())) && input->getMouseKeyDown(0)) {
    sceneState = Superscene::DESTROY;
  }
}
