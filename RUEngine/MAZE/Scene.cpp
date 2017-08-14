#include "Scene.h"
#include <stdlib.h>
#include <time.h>



Scene::Scene(Input* input) : Superscene(input)
{
  timer->timer.start();
  rows = 40;
  std::cout << "Scene initialized" << std::endl;
  srand(time(0));

  for (unsigned int i =0; i < rows; i++) {
    std::vector<Cell> row;
    for (unsigned int j = 0; j < rows; j ++) {
        //Create a mesh
        Entity* cells = new Entity();
        cells->LoadObject("Assets/untitled.obj", false);
        //Set a texture to it
        cells->position = glm::vec3(i,0,j);
        cells->scale = glm::vec3(0.5f,0.5f,0.5f);
        if (rand() % 2 == 1 || rand() % 3 == 2 )
        {
          cells->setColor(glm::vec3(1,1,1));
          cells->enabled = true;
        } else {
          cells->setColor(glm::vec3(0,0,0));
          cells->enabled = false;
        }
        //Add a child to the stage
        Cell madeCell;
        madeCell.entity = cells;
        cells->enabled = true;
        this->addChild(cells);
        row.push_back(madeCell);
    }
    cells.push_back(row);
  }

  light = new Light();
  light->position = glm::vec3(20,10,20);
  light->setPosition(light->getPosition());
  light->setLightColor(glm::vec3(1,1,1));
  light->setStrength(70.5f);
  light->setSpecularStrength(0.2f);
  this->addLight(light);

  setGamma(1.5f);
  setExposure(0.6f);
}

Scene::~Scene()
{
  delete mesh;
  delete light;
}

void Scene::Update(float deltaTime)
{
  if (timer->timer.seconds() > 0.033f) {

  }
}
