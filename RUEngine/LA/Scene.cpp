#include "Scene.h"
#include "stdlib.h"

struct cell {
  Entity* entity;
};


Scene::Scene(Input* input) : Superscene(input)
{
  right = tex::loadTexture("Assets/dust.jpg");
  left = tex::loadTexture("Assets/bumps.jpg");
  currentcell = tex::loadTexture("Assets/wall.jpg");

  facing = glm::vec2(0,-1);
  direction = "right";

  timer->timer.start();
  rows = 60;
  std::cout << "Scene initialized" << std::endl;

  srand(421111);

  for (unsigned int i =0; i < rows; i++) {
    std::vector<Entity*> row;
    for (unsigned int j = 0; j < rows; j ++) {
        //Create a mesh
        Entity* cell = new Entity();
        cell->LoadObject("Assets/untitled.obj", false);
        //Set a texture to it
        if (rand() % 3 == 2) {
          cell->setTexture(right);
        } else {
          cell->setTexture(left);
        }
        cell->position = glm::vec3(i,0,j);
        cell->scale = glm::vec3(0.5f,0.5f,0.5f);
        cell->enabled = true;
        if (i==30 && j==30)
        {
          cell->setTexture(currentcell);
        }
        //Add a child to the stage
        this->addChild(cell);
        row.push_back(cell);
    }
    cells.push_back(row);
  }

  light = new Light();
  light->position = glm::vec3(30,10,30);
  light->setPosition(light->getPosition());
  light->setLightColor(glm::vec3(1,1,1));
  light->setStrength(10.5f);
  light->setSpecularStrength(10.2f);
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
    for (unsigned int i =0; i < rows; i++) {
      for (unsigned int j = 0; j < rows; j ++) {
        if (cells[i][j]->getTexture() == currentcell)
        {
          if (i-1 >= 0 && i+1 < rows-1 && j-1 >= 0 && j+1 < rows-1)
          {
            if (facing.y == -1 && facing.x == 0) {
              if (direction == "right")
              {
                //MOVE X + 1
                facing = glm::vec2(1,0);
                cells[i][j]->setTexture(left);
                if (cells[i][j+1]->getTexture() == right) { direction = "right"; } else { direction = "left"; }
                cells[i][j+1]->setTexture(currentcell);
              } else {
                //MOVE X - 1
                facing = glm::vec2(-1,0);
                cells[i][j]->setTexture(right);
                if (cells[i][j-1]->getTexture() == right) { direction = "right"; } else { direction = "left"; }
                cells[i][j-1]->setTexture(currentcell);
              }
            }
            else if (facing.y == 1 && facing.x == 0) {
              if (direction == "right")
              {
                facing = glm::vec2(-1,0);
                cells[i][j]->setTexture(left);
                if (cells[i][j-1]->getTexture() == right) { direction = "right"; } else { direction = "left"; }
                cells[i][j-1]->setTexture(currentcell);
              } else {
                facing = glm::vec2(1,0);
                cells[i][j]->setTexture(right);
                if (cells[i][j+1]->getTexture() == right) { direction = "right"; } else { direction = "left"; }
                cells[i][j+1]->setTexture(currentcell);
              }
            }
            else if (facing.y == 0 && facing.x == 1) {
              if (direction == "right")
              {
                facing = glm::vec2(0,1);
                cells[i][j]->setTexture(left);
                if (cells[i + 1][j]->getTexture() == right) { direction = "right"; } else { direction = "left"; }
                cells[i + 1][j]->setTexture(currentcell);
              } else {
                facing = glm::vec2(0,-1);
                cells[i][j]->setTexture(right);
                if (cells[i - 1][j]->getTexture() == right) { direction = "right"; } else { direction = "left"; }
                cells[i - 1][j]->setTexture(currentcell);
              }
            }
            else if (facing.y == 0 && facing.x == -1) {
              if (direction == "right")
              {
                facing = glm::vec2(0,-1);
                cells[i][j]->setTexture(left);
                if (cells[i - 1][j]->getTexture() == right) { direction = "right"; } else { direction = "left"; }
                cells[i - 1][j]->setTexture(currentcell);
              } else {
                facing = glm::vec2(0,1);
                cells[i][j]->setTexture(right);
                if (cells[i + 1][j]->getTexture() == right) { direction = "right"; } else { direction = "left"; }
                cells[i + 1][j]->setTexture(currentcell);
              }
            }
          }
        return;
      }
    }
  }
}
