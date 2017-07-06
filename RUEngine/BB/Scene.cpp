#include "Scene.h"
#include <stdlib.h>
#include <time.h>



Scene::Scene(Input* input) : Superscene(input)
{
  timer->timer.start();
  rows = 100;
  std::cout << "Scene initialized" << std::endl;
  GLuint texture = tex::loadTexture("Assets/fur.jpg");
  GLuint texture1 = tex::loadTexture("Assets/dust.jpg");
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
        if (rand() % 2 == 1 || rand() % 2 == 1 )
        {
          cells->enabled = true;
          madeCell.state = ON;
        } else {
          cells->enabled = false;
          madeCell.state = OFF;
        }
        this->addChild(cells);
        row.push_back(madeCell);
    }
    cells.push_back(row);
  }

  light = new Light();
  light->position = glm::vec3(50,10,50);
  light->setPosition(light->getPosition());
  light->setLightColor(glm::vec3(1,1,1));
  light->setStrength(10.5f);
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
  if (timer->timer.seconds() > 0.1f) {
    std::vector<std::vector<States>> tempCells;
    for (unsigned int i =0; i < rows; i++) {
      std::vector<States> tempBools;
      for (unsigned int j = 0; j < rows; j ++) {
        tempBools.push_back(cells[i][j].state);
        int neighbours = 0;
        if (i != 0) {
          if ( cells[i-1][j].state == ON) {
            neighbours += 1;
          }
          if (j != rows - 1  && cells[i-1][j + 1].state == ON) {
            neighbours += 1;
          }
          if (j != 0  && cells[i - 1][j - 1].state == ON) {
            neighbours += 1;
          }
        }
        if (i != rows - 1) {
          if (cells[i + 1][j].state == ON) {
            neighbours += 1;
          }
          if (j != rows - 1  && cells[i + 1][j + 1].state == ON) {
            neighbours += 1;
          }
          if (j != 0  && cells[i+1][j - 1].state == ON) {
            neighbours += 1;
          }
        }
        if (j != rows - 1 && cells[i][j + 1].state == ON) {
          neighbours += 1;
        }
        if (j != 0 && cells[i][j - 1].state == ON) {
          neighbours += 1;
        }

        if (neighbours == 2 && cells[i][j].state == OFF)
        {
          tempBools[j] = ON;
        }
        else if (cells[i][j].state == DYING)
        {
          tempBools[j] = OFF;
        }
        else if (cells[i][j].state == ON)
        {
          tempBools[j] = DYING;
        }
      }
      tempCells.push_back(tempBools);
    }
    for (unsigned int i =0; i < rows; i++) {
      for (unsigned int j = 0; j < rows; j ++) {
        cells[i][j].state = tempCells[i][j];
        if (tempCells[i][j] == ON && cells[i][j].entity->enabled != true)
        {
          cells[i][j].entity->enabled = true;
          cells[i][j].entity->scale = glm::vec3(0.5f,0.5f,0.5f);
      } else if (tempCells[i][j] == DYING && cells[i][j].entity->enabled != true) {
          cells[i][j].entity->enabled = true;
          cells[i][j].entity->scale = glm::vec3(0.25f,0.25f,0.25f);
        } else if (cells[i][j].entity->enabled != false) {
          cells[i][j].entity->enabled = false;
        }
      }
    }
    timer->timer.start();
  }
}
