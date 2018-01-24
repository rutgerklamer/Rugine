#include "StartMenu.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iterator>

StartMenu::StartMenu(Input* input) : Superscene(input)
{
  // Make a entity
  hud = new Entity();
  // Make it 2D (GUI element)
  hud->make2D();
  // Set the scale of this entity
  hud->scale  = glm::vec3(0.5,0.5,1);
  // Set the color of this entity
  hud->setTexture(tex::loadTexture("Assets/start.png"));
  // Set the position of this entity according to the screen size
  hud->position = glm::vec3(1024.0/3.0f,720/2.0f,0);
  // Add this entity to the list of children (rendertargets)
  this->addChild(hud);

  // See above
  hud2 = new Entity();
  hud2->make2D();
  hud2->scale  = glm::vec3(0.5,0.5,1);
  hud2->setTexture(tex::loadTexture("Assets/quit.png"));
  hud2->position = glm::vec3(1024 - 1024.0/3.0f,720/2.0f,0);
  this->addChild(hud2);
}

StartMenu::~StartMenu()
{
  
}

void StartMenu::Update(float deltaTime)
{
  // If we click on this element
  if (Collision::intersectMouse2D(hud, glm::vec2(input->getMousePosition())) && input->getMouseKeyDown(0)) {
    // Switch to the next scene
    sceneState = Superscene::NEXT;
  }
  // If we click on this element
  if (Collision::intersectMouse2D(hud2, glm::vec2(input->getMousePosition())) && input->getMouseKeyDown(0)) {
     // Switch to the next scene
    sceneState = Superscene::DESTROY;
  }
}
