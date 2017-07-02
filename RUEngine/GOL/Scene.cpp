#include "Scene.h"
#include "stdlib.h"

struct cell {
  Entity* entity;
};

Scene::Scene(Input* input) : Superscene(input)
{
  timer->timer.start();
  rows = 40;
  std::cout << "Scene initialized" << std::endl;
  GLuint texture = tex::loadTexture("Assets/dirt.jpg");
  srand(2423);

  for (unsigned int i =0; i < rows; i++) {
    std::vector<Entity*> row;
    for (unsigned int j = 0; j < rows; j ++) {
        //Create a mesh
        Entity* cell = new Entity();
        cell->LoadObject("Assets/untitled.obj", false);
        //Set a texture to it
        cell->setTexture(texture);
        cell->position = glm::vec3(i,0,j);
        cell->scale = glm::vec3(0.5f,0.5f,0.5f);
        //Add a child to the stage
        int ran = rand() % 10;
        std::cout << ran << std::endl;
        if (ran == 5) {
          cell->enabled = true;
        } else {
          cell->enabled = false;
        }
        this->addChild(cell);
        row.push_back(cell);
    }
    cells.push_back(row);
  }


  light = new Light();
  light->position = glm::vec3(0,20,20);
  light->setPosition(light->getPosition());
  light->setLightColor(glm::vec3(1,1,1));
  light->setStrength(4.5f);
  light->setSpecularStrength(0.2f);
  this->addLight(light);

  setGamma(0.8f);
  setExposure(0.3f);
}

Scene::~Scene()
{
  delete mesh;
  delete light;
}

void Scene::Update(float deltaTime)
{
  if (timer->timer.seconds() > 0.5f) {
    for (unsigned int i =0; i < rows; i++) {
      for (unsigned int j = 0; j < rows; j ++) {
        int neighbours = 0;
        if (i != 0) {
          if (cells[i-1][j]->enabled) {
            neighbours += 1;
          }
          if (j != rows - 1 && cells[i-1][j + 1]->enabled) {
            neighbours += 1;
          }
          if (j != 0 && cells[i-1][j - 1]->enabled) {
            neighbours += 1;
          }
        }
        if (i != rows - 1) {
          if (cells[i+1][j]->enabled) {
            neighbours += 1;
          }
          if (j != rows - 1 && cells[i+1][j + 1]->enabled) {
            neighbours += 1;
          }
          if (j != 0 && cells[i+1][j - 1]->enabled) {
            neighbours += 1;
          }
        }
        if (j != rows - 1 && cells[i][j + 1]->enabled) {
          neighbours += 1;
        }
        if (j != 0 && cells[i][j - 1]->enabled) {
          neighbours += 1;
        }
        if (neighbours < 2) {
          cells[i][j]->enabled = false;
        } else if (neighbours == 3 && cells[i][j]->enabled || neighbours == 2 && cells[i][j]->enabled) {
          cells[i][j]->enabled = true;
        } else if (neighbours > 3) {
          cells[i][j]->enabled = false;
        } else if (!cells[i][j]->enabled && neighbours == 3) {
          cells[i][j]->enabled = true;
        }
      }
    }
    timer->timer.start();
  }
}
