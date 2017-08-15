#include "Scene.h"
#include <stdlib.h>
#include <time.h>



Scene::Scene(Input* input) : Superscene(input)
{
  timer->timer.start();
  rows = 41;
  std::cout << "Scene initialized" << std::endl;
  srand(time(0));

  for (unsigned int i =0; i < rows; i++) {
    std::vector<Cell> row;
    for (unsigned int j = 0; j < rows; j ++) {
        //Create a mesh
        Entity* cells = new Entity();
        cells->LoadObject("Assets/untitled.obj", false);
        //Set a texture to it
        cells->setColor(glm::vec3(1,1,1));
        cells->position = glm::vec3(i,0,j);
        cells->scale = glm::vec3(0.5f,0.5f,0.5f);
        //Add a child to the stage
        Cell madeCell;
        madeCell.entity = cells;
        cells->enabled = true;
        this->addChild(cells);
        row.push_back(madeCell);
    }
    cells.push_back(row);
  }
  for (unsigned int x = 0; x < rows/2 + 1; x++)
  {
    for (unsigned int y = 0; y < rows/2 + 1; y++)
    {
        cells[x*2.0][y*2.0].entity->setColor(glm::vec3(0,0,0));
    }
  }
  int x = (rows - 1) / 2 - 1;
  int y = (rows - 1) / 2 - 1;

  std::cout << x << "      " << y << std::endl;
  walkerPos = glm::vec2(x,y);
  cells[x][y].visited = true;
  cells[x][y].entity->setColor(glm::vec3(1,0,1));
  visitedStack.push_back(cells[x][y]);
  difficulty = HARD;

  if (difficulty == HARD) {
    while (GenerateMazeHard()){}
    while (true) {
      glm::vec2 temp = glm::vec2(rand() % rows, rand() % rows);
      if (cells[temp.x][temp.y].entity->getColor() == glm::vec3(1,1,1)) {
        end = temp;
        break;
      }
    }
  }

  cells[end.x][end.y].entity->setColor(glm::vec3(0,1,0));
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

bool Scene::GenerateMazeHard()
{
    glm::vec2 nextMove;
    int rando = floor(rand() % 4);
    std::cout << amount << "        " << rows*rows << std::endl;
    Dir direction = static_cast<Dir>(rand() % 4);
    if (direction == N)
    {
      nextMove = glm::vec2(0,-2);
    } else if (direction == S) {
      nextMove = glm::vec2(0,2);
    } else if (direction == E) {
      nextMove = glm::vec2(2,0);
    } else if (direction == W) {
      nextMove = glm::vec2(-2,0);
    }

    if (direction == N && walkerPos.y-2 >= 0 || direction == S && walkerPos.y+2 < rows || direction == E && walkerPos.x+2 < rows || direction == W && walkerPos.x-2 >= 0)
    {
      if (!cells[walkerPos.x + nextMove.x][walkerPos.y+nextMove.y].visited) {
      //  cells[walkerPos.x + nextMove.x][walkerPos.y+nextMove.y].entity->setColor(glm::vec3(1,0,0));
        cells[walkerPos.x + nextMove.x][walkerPos.y+nextMove.y].visited = true;
        visitedStack.push_back(cells[walkerPos.x + nextMove.x][walkerPos.y+nextMove.y]);
        end = walkerPos;
        walkerPos += nextMove;
        Paint(direction);
      } else if (walkerPos.x + 2 < rows && !cells[walkerPos.x + 2][walkerPos.y].visited || walkerPos.y + 2 < rows && !cells[walkerPos.x][walkerPos.y + 2].visited || walkerPos.y - 2 >= 0 && !cells[walkerPos.x][walkerPos.y - 2].visited || walkerPos.x - 2 >= 0 && !cells[walkerPos.x - 2][walkerPos.y].visited)
      {
        return true;
      } else if (visitedStack.size() > 0) {
        walkerPos = glm::vec2(visitedStack[visitedStack.size() - 1].entity->getPosition().x, visitedStack[visitedStack.size() - 1].entity->getPosition().z);
        visitedStack.pop_back();
      } else {
        std::cout << "done" << std::endl;
        return false;
      }
  }
  return true;
}

void Scene::Paint(Dir dir)
{
  if (dir == N ) {
    if (walkerPos.y - 1 >= 0)
    {
      cells[walkerPos.x][walkerPos.y-1].entity->setColor(glm::vec3(0,0,0));
    }
    if (walkerPos.y + 1 < rows)
    {
      cells[walkerPos.x][walkerPos.y+1].entity->setColor(glm::vec3(1,1,1));
    }
  }
  if (dir == S) {
    if (walkerPos.y + 1 < rows)
    {
      cells[walkerPos.x][walkerPos.y+1].entity->setColor(glm::vec3(0,0,0));
    }
    if (walkerPos.y - 1 >= 0)
    {
      cells[walkerPos.x][walkerPos.y-1].entity->setColor(glm::vec3(1,1,1));
    }
  }
  if (dir == W)
  {
    if (walkerPos.x - 1 >= 0)
    {
      cells[walkerPos.x - 1][walkerPos.y].entity->setColor(glm::vec3(0,0,0));
    }
    if (walkerPos.x + 1 < rows)
    {
      cells[walkerPos.x + 1][walkerPos.y].entity->setColor(glm::vec3(1,1,1));
    }
  }
  if (dir == E)
  {
    if (walkerPos.x + 1 < rows)
    {
      cells[walkerPos.x + 1][walkerPos.y].entity->setColor(glm::vec3(0,0,0));
    }
    if (walkerPos.x - 1 >= 0)
    {
      cells[walkerPos.x - 1][walkerPos.y].entity->setColor(glm::vec3(1,1,1));
    }
  }
  if (dir == W || dir == E)
  {
    if (walkerPos.y - 1 >= 0)
    {
      cells[walkerPos.x][walkerPos.y - 1].entity->setColor(glm::vec3(0,0,0));
    }
    if (walkerPos.y + 1 < rows)
    {
      cells[walkerPos.x][walkerPos.y+1].entity->setColor(glm::vec3(0,0,0));
    }
  }
  if (dir == S || dir == N) {
    if (walkerPos.x - 1 >= 0)
    {
      cells[walkerPos.x - 1][walkerPos.y].entity->setColor(glm::vec3(0,0,0));
    }
    if (walkerPos.x + 1 < rows)
    {
      cells[walkerPos.x + 1][walkerPos.y].entity->setColor(glm::vec3(0,0,0));
    }
  }
}

void Scene::Update(float deltaTime)
{
  if (timer->timer.seconds() > 0.0f) {
    timer->timer.start();
  }
}
