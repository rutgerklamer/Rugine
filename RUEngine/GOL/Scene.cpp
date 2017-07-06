#include "Scene.h"
#include <stdlib.h>
#include <time.h>



Scene::Scene(Input* input) : Superscene(input)
{
  timer->timer.start();
  rows = 40;
  std::cout << "Scene initialized" << std::endl;
  GLuint texture = tex::loadTexture("Assets/dust.jpg");
  GLuint texture2 = tex::loadTexture("Assets/bumps.jpg");
  srand(time(0));

  for (unsigned int i =0; i < rows; i++) {
    std::vector<Cell> row;
    for (unsigned int j = 0; j < rows; j ++) {
        //Create a mesh
        Entity* cells = new Entity();
        cells->LoadObject("Assets/untitled.obj", false);
        //Set a texture to it
        cells->setTexture(texture);
        cells->position = glm::vec3(i,0,j);
        cells->scale = glm::vec3(0.5f,0.5f,0.5f);
        //Add a child to the stage
        Cell madeCell;
        madeCell.entity = cells;
        if (j % 2 > 0 || rand() % 3 == 2 )
        {
          cells->setTexture(texture2);
          cells->enabled = true;
        } else {
          cells->enabled = false;
        }
        this->addChild(cells);
        row.push_back(madeCell);
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
        tempBools.push_back(cells[i][j].entity->enabled);
        int neighbours = 0;
        if (i != 0) {
          if (cells[i-1][j].entity->enabled) {
            neighbours += 1;
          }
          if (j != rows - 1 && cells[i-1][j + 1].entity->enabled) {
            neighbours += 1;
          }
          if (j != 0 && cells[i-1][j - 1].entity->enabled) {
            neighbours += 1;
          }
        }
        if (i != rows - 1) {
          if (cells[i+1][j].entity->enabled) {
            neighbours += 1;
          }
          if (j != rows - 1 && cells[i+1][j + 1].entity->enabled) {
            neighbours += 1;
          }
          if (j != 0 && cells[i+1][j - 1].entity->enabled) {
            neighbours += 1;
          }
        }
        if (j != rows - 1 && cells[i][j + 1].entity->enabled) {
          neighbours += 1;
        }
        if (j != 0 && cells[i][j - 1].entity->enabled) {
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
        cells[i][j].entity->enabled = tempCells[i][j];
      }
    }
    timer->timer.start();
  }
}
