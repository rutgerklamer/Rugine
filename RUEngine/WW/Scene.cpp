#include "Scene.h"
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iterator>

Scene::Scene(Input* input) : Superscene(input)
{
  timer->timer.start();
  rows = 50;
  std::cout << "Scene initialized" << std::endl;
  srand(time(0));

  red = tex::loadTexture("Assets/red.png");
  grey = tex::loadTexture("Assets/grey.png");
  yellow = tex::loadTexture("Assets/yellow.png");
  blue = tex::loadTexture("Assets/blue.png");

  readFile("Assets/grid2.txt");
  makeGrid();


  light = new Light();
  light->position = glm::vec3(25,10,25);
  light->setPosition(light->getPosition());
  light->setLightColor(glm::vec3(1,1,1));
  light->setStrength(113.5f);
  light->setSpecularStrength(0.2f);
  this->addLight(light);

  setGamma(0.8f);
  setExposure(0.1f);
}

Scene::~Scene()
{
  delete mesh;
  delete light;
}

void Scene::checkMovement()
{
  for (unsigned int i =0; i < rows; i++) {
    for (unsigned int j = 0; j < rows; j ++) {
      if (camera->getPosition().x <= i && camera->getPosition().x >= i-1 && camera->getPosition().z <= j && camera->getPosition().z >= j-1) {
        std::cout << " X ( " << i << " ) Y ( " << j << " )" << std::endl;
        cells[i][j].entity->enabled = false;
      } else {
        cells[i][j].entity->enabled = true;
      }
      if (input->isDown(GLFW_KEY_SPACE) && i >= 0 && j >= 0 && i< rows && j < rows && !cells[i][j].entity->enabled)
      {
        input->setKey(GLFW_KEY_SPACE, false);
        if (cells[i][j].state == OFF)
        {
          cells[i][j].state = WIRE;
        }
        else if (cells[i][j].state == WIRE)
        {
          cells[i][j].state = HEAD;
        }
        else if (cells[i][j].state == WIRE)
        {
          cells[i][j].state = TAIL;
        }
        else
        {
          cells[i][j].state = OFF;
        }
      }
    }
  }
}

void Scene::Update(float deltaTime)
{
  checkMovement();
  if (input->isDown(GLFW_KEY_R))
  {
    input->setKey(GLFW_KEY_R, false);
    makeGrid();
  }
  if (timer->timer.seconds() > 0.1f) {
    std::vector<std::vector<States>> tempCells;
    for (unsigned int i =0; i < rows; i++) {
      std::vector<States> tempBools;
      for (unsigned int j = 0; j < rows; j ++) {


        tempBools.push_back(cells[i][j].state);
        int neighbours = 0;
        if (i != 0) {
          if (cells[i-1][j].state == HEAD) {
            neighbours += 1;
          }
          if (j != rows - 1 && cells[i-1][j + 1].state == HEAD) {
            neighbours += 1;
          }
          if (j != 0 && cells[i-1][j - 1].state == HEAD) {
            neighbours += 1;
          }
        }
        if (i != rows - 1) {
          if (cells[i+1][j].state == HEAD) {
            neighbours += 1;
          }
          if (j != rows - 1 && cells[i+1][j + 1].state == HEAD) {
            neighbours += 1;
          }
          if (j != 0 && cells[i+1][j - 1].state == HEAD) {
            neighbours += 1;
          }
        }
        if (j != rows - 1 && cells[i][j + 1].state == HEAD) {
          neighbours += 1;
        }
        if (j != 0 && cells[i][j - 1].state == HEAD) {
          neighbours += 1;
        }

        if (cells[i][j].state == HEAD)
        {
          tempBools[j] = TAIL;
        }
        else if (cells[i][j].state == OFF)
        {
          tempBools[j] = OFF;
        }
        else if (cells[i][j].state == TAIL)
        {
          tempBools[j] = WIRE;
        }
        else if (cells[i][j].state == WIRE && neighbours > 0 && neighbours < 3)
        {
          tempBools[j] = HEAD;
        }


      }
      tempCells.push_back(tempBools);
    }
    currentAmount = 0;
    for (unsigned int i =0; i < rows; i++) {
      for (unsigned int j = 0; j < rows; j ++) {
        cells[i][j].state = tempCells[i][j];
        if (cells[i][j].state == HEAD)
        {
          cells[i][j].entity->setTexture(red);
        }
        else if (cells[i][j].state == OFF)
        {
          cells[i][j].entity->setTexture(grey);
        }
        else if (cells[i][j].state == TAIL)
        {
          cells[i][j].entity->setTexture(blue);
        }
        else if (cells[i][j].state == WIRE)
        {
          cells[i][j].entity->setTexture(yellow);
        }
        // if (cells[i][j].state == HEAD && finishedGrid[i][j] == '5')
        // {
        //   currentAmount += 1;
        // }
        // if (cells[i][j].state == HEAD && finishedGrid[i][j] == '6')
        // {
        //   currentAmount += 2;
        // }
    }
  }
  // if (currentAmount == 1)
  // {
  //   std::cout << "Total amount is 1" << "In binary it is 01" << std::endl;
  // }
  // else if (currentAmount == 2)
  // {
  //   std::cout << "Total amount is 2" << "In binary it is 10" << std::endl;
  // }
  // else if (currentAmount == 3)
  // {
  //   std::cout << "Total amount is 3" << "In binary it is 11" << std::endl;
  // }
    timer->timer.start();
  }
}

void Scene::readFile(const char* filename)
{
  std::ifstream infile(filename);

  std::string line;
  while (std::getline(infile, line))
      finishedGrid.push_back(line);

  std::cout << finishedGrid[1][0] << std::endl;
  infile.close();
}

void Scene::makeGrid()
{
  if (cells.size() > 0) {
    entities.clear();
    for (unsigned int k = 0; k < rows; k++) {
      for (unsigned int l = 0 ; l < rows; l++) {
        delete cells[k][l].entity;
      }
    }
  }
  for (unsigned int i =0; i < rows; i++) {
    std::vector<Cell> row;
    for (unsigned int j = 0; j < rows; j ++) {
        //Create a mesh
        Entity* cells = new Entity();
        cells->LoadObject("Assets/untitled.obj", false);
        //Set a texture to it
    //    cells->setTexture(red);
        cells->position = glm::vec3(i,0,j);
        cells->scale = glm::vec3(0.5f,0.5f,0.5f);
        //Add a child to the stage
        Cell madeCell;
        madeCell.entity = cells;
        if (finishedGrid[i][j] == '0')
        {
          cells->setTexture(grey);
          madeCell.state = OFF;
        }
        else if (finishedGrid[i][j] == '1' || finishedGrid[i][j] == '5' || finishedGrid[i][j] == '6')
        {
          cells->setTexture(yellow);
          madeCell.state = WIRE;
        }
        else if (finishedGrid[i][j] == '2')
        {
          cells->setTexture(blue);
          madeCell.state = TAIL;
        }
        else if (finishedGrid[i][j] == '3')
        {
          cells->setTexture(red);
          madeCell.state = HEAD;
        }
        this->addChild(cells);
        row.push_back(madeCell);
    }
    if (cells.size() == rows) {
      cells.clear();
    }
    cells.push_back(row);
    }
  }
