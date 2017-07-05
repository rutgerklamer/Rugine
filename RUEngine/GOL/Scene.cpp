#include "Scene.h"
#include "stdlib.h"

struct cell {
  Entity* entity;
};

Scene::Scene(Input* input) : Superscene(input)
{
  timer->timer.start();
  rows = 100;
  std::cout << "Scene initialized" << std::endl;
  GLuint texture = tex::loadTexture("Assets/dust.jpg");
  GLuint texture2 = tex::loadTexture("Assets/bumps.jpg");
  srand(421111);

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
        if (j % 2 > 0 || rand() % 3 == 2 )
        {
          cell->setTexture(texture2);
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
  light->position = glm::vec3(70,20,70);
  light->setPosition(light->getPosition());
  light->setLightColor(glm::vec3(1,1,1));
  light->setStrength(70.5f);
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
  if (timer->timer.seconds() > 0.0001f) {
    std::vector<std::vector<bool>> tempCells;
    for (unsigned int i =0; i < rows; i++) {
      std::vector<bool> tempBools;
      for (unsigned int j = 0; j < rows; j ++) {
        tempBools.push_back(cells[i][j]->enabled);
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
          tempBools[j] = false;
        } else if (neighbours > 3) {
          tempBools[j] = false;
        } else if (neighbours == 3){
          tempBools[j] = true;
        }
      }
      tempCells.push_back(tempBools);
    }
    for (unsigned int i =0; i < rows; i++) {
      for (unsigned int j = 0; j < rows; j ++) {
        cells[i][j]->enabled = tempCells[i][j];
      }
    }
    timer->timer.start();
  }
}
